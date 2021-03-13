#include "M11BT222A.h"

// Check the PT6311 datasheet for the commands

// Display mode setting command: 11 digits, 17 segments (0000 1010)
#define DMSC_11D_17S 0x0A

// Display control command: set display pwm from 1/16 to 14/16 on, also the screen can be turned off
#define DCC_ON 0x88
#define DCC_OFF 0x80

// Data setting command: Write Increment, normal mode (0100 0000)
#define DSC_W_INC_N 0x40

// Address setting command: Adress 0 (1100 0000)
#define ASC_START 0xC0

// Set all the pins
M11BT222A::M11BT222A(int8_t enable_pin, int8_t data_in_pin, int8_t clock_pin, int8_t strobe_pin)
{
	en_pin = enable_pin;
	din_pin = data_in_pin;
	clk_pin = clock_pin;
	stb_pin = strobe_pin;
	
	digitalWrite(en_pin, LOW);
	digitalWrite(din_pin, LOW);
	digitalWrite(clk_pin, HIGH);
	digitalWrite(stb_pin, HIGH);

	pinMode(en_pin, OUTPUT);
	pinMode(din_pin, OUTPUT);
	pinMode(clk_pin, OUTPUT);
	pinMode(stb_pin, OUTPUT);

	digitalWrite(en_pin, HIGH);
}

// Configure the display 
void M11BT222A::initDisplay()
{
	initDisplay(4);	
}

void M11BT222A::initDisplay(unsigned char brightness)
{
	// Clamp the values
	if (brightness > 7) brightness = 4;
	
	delay(200);
	
	digitalWrite(stb_pin, LOW);
	digitalWrite(clk_pin, LOW);
	digitalWrite(din_pin, HIGH);  

	__asm__("nop\nnop\n");

	clearDisplay();
	writeCommand(DMSC_11D_17S); // DMSC: 11 digits x 17 segments
	setBrightness(brightness);
}

void M11BT222A::clearDisplay()
{
	writeMemory(0x00); 	// Clear all segments
	
	memset(digitRam, 0x00, sizeof(digitRam)); // Clear digit ram array
	recRam = 0x00; // Clear rec ram
	networkRam = 0x00; // Clear network ram
	blocksRam = 0x0000; // Clear blocks ram	
	dotsRam = 0x00; // Clear dots ram	
	discRam = 0x00; // Clear disc ram	
}

void M11BT222A::setBrightness(unsigned char brightness)
{
	// Clamp the values
	if (brightness > 7) return;
	
	brightnessRam = brightness;
	writeCommand(DCC_ON | brightness);
}

void M11BT222A::toggleDisplay(bool show)
{
	if (show)
		writeCommand(DCC_ON | brightnessRam);
	else
		writeCommand(DCC_OFF);
}

// ===========================================================================
//   7 SEGMENT FUNCTIONS
// ===========================================================================

void M11BT222A::showNumbers(unsigned char val0, unsigned char val1, unsigned char val2, unsigned char val3, unsigned char val4, unsigned char val5, bool colon1, bool colon2)
{
	showColon(0, colon1);
	showColon(1, colon1);
	showColon(2, colon2);
	showColon(3, colon2);
	
	showNumbers(val0, val1, val2, val3, val4, val5);
}

void M11BT222A::showNumbers(unsigned char val0, unsigned char val1, unsigned char val2, unsigned char val3, unsigned char val4, unsigned char val5)
{
	// Clamp the values
	if (val0 > 15) val0 = 0x00;
	if (val1 > 15) val1 = 0x00;
	if (val2 > 15) val2 = 0x00;
	if (val3 > 15) val3 = 0x00;
	if (val4 > 15) val4 = 0x00;
	if (val5 > 15) val5 = 0x00;
	
	
	showNumber(0x00, val0);
	showNumber(0x01, val1);
	showNumber(0x02, val2);
	showNumber(0x03, val3);
	showNumber(0x04, val4);
	showNumber(0x05, val5);	
}

void M11BT222A::showNumber(unsigned char seg, unsigned char val)
{
	// Clamp the values
	if (seg > 5) return;
	if (val > 0x0F) val = 0x00;
	
	showNumberCustom(seg, digitData[val]);
}

void M11BT222A::hideNumber(unsigned char seg)
{
	// Clamp the values
	if (seg > 5) return;
	
	showNumberCustom(seg, 0x00);
}

void M11BT222A::showNumberCustom(unsigned char seg, unsigned char data)
{
	// Clamp the values
	if (seg > 5) return;

	unsigned char addr, colonData;
	
	if (seg == 0)
		addr = ADDR_DIGIT_0;
	else if (seg == 1)
		addr = ADDR_DIGIT_1;
	else if (seg == 2)
		addr = ADDR_DIGIT_2;
	else if (seg == 3)
		addr = ADDR_DIGIT_3;
	else if (seg == 4)
		addr = ADDR_DIGIT_4;
	else
		addr = ADDR_DIGIT_5;
	
	// Keep the colon info
	colonData = digitRam[addr - ADDR_DIGIT_0];
	colonData &= 0x80;
	
	// Remove the colon info from the digit data
	data &= 0x7F;
	
	data = data | colonData;
	
	digitRam[addr - ADDR_DIGIT_0] = data;
	
	writeDisplayRam(addr, data);
}

void M11BT222A::showColons(bool colon1, bool colon2, bool colon3, bool colon4)
{
	showColon(0, colon1);
	showColon(1, colon2);
	showColon(2, colon3);
	showColon(3, colon4);
}

void M11BT222A::showColon(int8_t index, bool visible)
{
	unsigned char addr, data, digitData;
	
	if (index == 0)
		addr = ADDR_COLON_0;
	else if (index == 1)
		addr = ADDR_COLON_1;
	else if (index == 2)
		addr = ADDR_COLON_2;
	else if (index == 3)
		addr = ADDR_COLON_3;
	else return;
	
	data = (visible) ? 0x80 : 0x00; 
	
	// Keep the digit info
	digitData = digitRam[addr - ADDR_DIGIT_0];
	digitData &= 0x7F;
	
	data = data | digitData;
	digitRam[addr - ADDR_DIGIT_0] = data;
		
	writeDisplayRam(addr, data);
}


// ===========================================================================
//   15 SEGMENT FUNCTIONS
// ===========================================================================

void M11BT222A::showCharacter(unsigned char seg, unsigned char letter)
{	
	if (letter < 32 || letter > 127) letter = 127;

	unsigned int data = charData[(int)letter - 32];
	
	showCharacterCustom(seg, data);
}

void M11BT222A::hideCharacter(unsigned char seg)
{
	// Clamp the values
	if (seg > 4) return;
	
	showCharacterCustom(seg, 0x0000);
}

void M11BT222A::showCharacterCustom(unsigned char seg, unsigned int data)
{
	// Clamp the values
	if (seg > 4) return;

	unsigned char addr_top, addr_bot, data_top, data_bottom;
	
	data_top = data >> 8;
	data_bottom = data;
	
	if (seg == 0)
	{
		addr_top = ADDR_LETTER_0_TOP;
		addr_bot = ADDR_LETTER_0_BOT;
	}
	else if (seg == 1)
	{
		addr_top = ADDR_LETTER_1_TOP;
		addr_bot = ADDR_LETTER_1_BOT;
	}
	else if (seg == 2)
	{
		addr_top = ADDR_LETTER_2_TOP;
		addr_bot = ADDR_LETTER_2_BOT;
	}
	else if (seg == 3)
	{
		addr_top = ADDR_LETTER_3_TOP;
		addr_bot = ADDR_LETTER_3_BOT;
	}
	else
	{
		addr_top = ADDR_LETTER_4_TOP;
		addr_bot = ADDR_LETTER_4_BOT;
	}
	
	writeDisplayRam(addr_top, data_top);
	writeDisplayRam(addr_bot, data_bottom);
}

// ===========================================================================
//   ICON FUNCTIONS
// ===========================================================================

// Toggle the AUTO icon
void M11BT222A::showIconAuto(bool visible)
{
	writeDisplayRam(ADDR_ICON_AUTO, (visible) ? 0xFF : 0x00);
}

// Toggle the EPG icon
void M11BT222A::showIconEpg(bool visible)
{
	writeDisplayRam(ADDR_ICON_EPG, (visible) ? 0xFF : 0x00);
}

// Toggle the TRANS icon
void M11BT222A::showIconTrans(bool visible)
{
	writeDisplayRam(ADDR_ICON_TRANS, (visible) ? 0xFF : 0x00);
}

// Toggle the MAIL icon
void M11BT222A::showIconMail(bool visible)
{
	writeDisplayRam(ADDR_ICON_MAIL, (visible) ? 0xFF : 0x00);
}

// Toggle the RATE icon
void M11BT222A::showIconRate(bool visible)
{
	writeDisplayRam(ADDR_ICON_RATE, (visible) ? 0xFF : 0x00);
}

// Toggle the TITLE icon
void M11BT222A::showIconTitle(bool visible)
{
	writeDisplayRam(ADDR_ICON_TITLE, (visible) ? 0xFF : 0x00);
}

// Toggle the CHP icon
void M11BT222A::showIconChp(bool visible)
{
	writeDisplayRam(ADDR_ICON_CHP, (visible) ? 0xFF : 0x00);
}

// Toggle the TRK icon
void M11BT222A::showIconTrk(bool visible)
{
	writeDisplayRam(ADDR_ICON_TRK, (visible) ? 0xFF : 0x00);
}

// Toggle the CH icon
void M11BT222A::showIconCh(bool visible)
{
	writeDisplayRam(ADDR_ICON_CH, (visible) ? 0xFF : 0x00);
}

// Toggle the HDD icon
void M11BT222A::showIconHdd(bool visible)
{
	if (visible)
		recRam |= (1 << 6);
	else
		recRam &= ~(1 << 6);
	
	writeDisplayRam(ADDR_ICON_DVD, recRam);
}

// Toggle the HDD Rec icon
void M11BT222A::showIconHddRec(bool visible)
{
	if (visible)
		recRam |= (1 << 7);
	else
		recRam &= ~(1 << 7);
	
	writeDisplayRam(ADDR_ICON_DVD, recRam);
}

// Toggle the DVD icon
void M11BT222A::showIconDvd(bool visible)
{
	if (visible)
		recRam |= (1 << 4);
	else
		recRam &= ~(1 << 4);
	
	writeDisplayRam(ADDR_ICON_DVD, recRam);
}

// Toggle the DVD Rec icon
void M11BT222A::showIconDvdRec(bool visible)
{
	if (visible)
		recRam |= (1 << 5);
	else
		recRam &= ~(1 << 5);
	
	writeDisplayRam(ADDR_ICON_DVD, recRam);
}

// Toggle the NETWORK icon
void M11BT222A::showIconNetwork(bool visible)
{
	if (visible)
		networkRam |= (1 << 15);
	else
		networkRam &= ~(1 << 15);
	
	writeDisplayRam(ADDR_ICON_NWORK, networkRam >> 8);
}

// Toggle the Music icon
void M11BT222A::showIconMusic(bool visible)
{
	if (visible)
		networkRam |= (1 << 7);
	else
		networkRam &= ~(1 << 7);
	
	writeDisplayRam(ADDR_ICON_MUSIC, networkRam);
}

// Toggle the USB icon
void M11BT222A::showIconUsb(bool visible)
{
	writeDisplayRam(ADDR_ICON_USB, (visible) ? 0xFF : 0x00);
}

// ===========================================================================
//   NETWORK FUNCTIONS
// ===========================================================================

void M11BT222A::toggleNetworkDots(unsigned int dots)
{
	// Prevent this function to turn on the Network or Music icons
	networkRam &= (dots & 0x77);
}

void M11BT222A::toggleNetworkDot(unsigned char index, bool visible)
{
	// Clamp the values
	if (index > 13) return;
	
	if (index < 7)
	{
		if (visible)
			networkRam |= (1 << index);
		else
			networkRam &= ~(1 << index);
	}
	else
	{
		if (visible)
			networkRam |= (1 << (index + 1));
		else
			networkRam &= ~(1 << (index + 1));
	}
}

void M11BT222A::clearNetworkDots()
{
	toggleNetworkDots(0);
}

void M11BT222A::updateNetworkDots()
{
	writeDisplayRam(ADDR_NETWORK_TOP, networkRam);
	writeDisplayRam(ADDR_NETWORK_BOT, networkRam  >> 8);
}

// ===========================================================================
//   BLOCK FUNCTIONS
// ===========================================================================

void M11BT222A::toggleBlocks(unsigned int blocks)
{
	blocksRam = blocks;
}

void M11BT222A::toggleBlock(unsigned char x, unsigned char y, bool visible)
{
	toggleBlock(0x0F - (y * 4 + x), visible);
}

void M11BT222A::toggleBlock(unsigned char index, bool visible)
{
	// Clamp the values
	if (index > 15) return;
	
	if (visible)
		blocksRam |= (1 << index);
	else
		blocksRam &= ~(1 << index);
}

void M11BT222A::updateBlocks()
{
	writeDisplayRam(ADDR_BLOCKS_TOP, blocksRam >> 8);
	writeDisplayRam(ADDR_BLOCKS_BOT, blocksRam);
}

// ===========================================================================
//   DOTS FUNCTIONS
// ===========================================================================

void M11BT222A::toggleDots(unsigned char dots)
{
	dotsRam = dots;
	writeDisplayRam(ADDR_DISC_DOTS, dotsRam);
}

void M11BT222A::toggleDot(unsigned char index, bool visible)
{
	// Clamp the values
	if (index > 3) return;
	
	if (visible)
		dotsRam |= (1 << index);
	else
		dotsRam &= ~(1 << index);
	
	writeDisplayRam(ADDR_DISC_DOTS, dotsRam);
}

// ===========================================================================
//   DISC FUNCTIONS
// ===========================================================================

void M11BT222A::toggleDisc(unsigned char index, bool visible)
{
	// Clamp the values
	if (index > 7) return;
	
	if (visible)
		discRam |= (1 << index);
	else
		discRam &= ~(1 << index);
	
	writeDisplayRam(ADDR_DISC_SPINNER, discRam);
}

void M11BT222A::toggleDisc(unsigned char disc)
{
	discRam = disc;	
	writeDisplayRam(ADDR_DISC_SPINNER, discRam);
}

// ===========================================================================
//   PT6311 COMMANDS
// ===========================================================================

// Write to the display RAM
void M11BT222A::writeDisplayRam(unsigned char addr, unsigned char data)
{
	writeCommand(DSC_W_INC_N);

	digitalWrite(stb_pin, HIGH);
	writeData(ASC_START | addr);
	writeData(data);

	digitalWrite(stb_pin, LOW);
	__asm__("nop\nnop\n");
}

// Write data to the display
void M11BT222A::writeData(unsigned char data)
{
	for (unsigned char c = 0; c < 8; c++)
	{
		digitalWrite(clk_pin, HIGH);

		if (data & 0x01)
			digitalWrite(din_pin, HIGH);
		else
			digitalWrite(din_pin, LOW);
	  
		data >>= 1;

		digitalWrite(clk_pin, LOW);
		__asm__("nop\nnop\n");
	}
}

// Write a command to the display
void M11BT222A::writeCommand(unsigned char cmd)
{
	digitalWrite(stb_pin, HIGH);
	writeData(cmd);

	digitalWrite(stb_pin, LOW);
	__asm__("nop\nnop\n");
}

// Write to the complete memory of the display
void M11BT222A::writeMemory(unsigned char mem)
{
	writeCommand(DSC_W_INC_N);

	digitalWrite(stb_pin, HIGH);
	writeData(ASC_START);

	for (unsigned char c = 0; c <= LAST_ADDRESS; c++)
	{
		writeData(mem);
	}

	digitalWrite(stb_pin, LOW);
  __asm__("nop\nnop\n");
}