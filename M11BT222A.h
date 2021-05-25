#ifndef M11BT222A_h
#define M11BT222A_h

#include <Arduino.h>

// Addresses
#define LAST_ADDRESS 0x20

#define ADDR_DIGIT_0 0x0F 		// DIGIT 0
#define ADDR_DIGIT_1 0x15 		// DIGIT 1
#define ADDR_DIGIT_2 0x16 		// DIGIT 2
#define ADDR_DIGIT_3 0x12 		// DIGIT 3
#define ADDR_DIGIT_4 0x13 		// DIGIT 4
#define ADDR_DIGIT_5 0x10 		// DIGIT 5

#define ADDR_COLON_0 0x15 		// DIGIT COLON 0
#define ADDR_COLON_1 0x16 		// DIGIT COLON 1
#define ADDR_COLON_2 0x12 		// DIGIT COLON 2
#define ADDR_COLON_3 0x13 		// DIGIT COLON 3

#define ADDR_LETTER_0_TOP 0x0C 	// LETTER 0 TOP
#define ADDR_LETTER_0_BOT 0x0D 	// LETTER 0 BOTTOM
#define ADDR_LETTER_1_TOP 0x09 	// LETTER 1 TOP
#define ADDR_LETTER_1_BOT 0x0A 	// LETTER 1 BOTTOM
#define ADDR_LETTER_2_TOP 0x06 	// LETTER 2 TOP
#define ADDR_LETTER_2_BOT 0x07 	// LETTER 2 BOTTOM
#define ADDR_LETTER_3_TOP 0x03 	// LETTER 3 TOP
#define ADDR_LETTER_3_BOT 0x04 	// LETTER 3 BOTTOM
#define ADDR_LETTER_4_TOP 0x00 	// LETTER 4 TOP 
#define ADDR_LETTER_4_BOT 0x01 	// LETTER 5 BOTTOM 

#define ADDR_ICON_AUTO	0x14 	// AUTO Icon
#define ADDR_ICON_EPG	0x17 	// EPG Icon
#define ADDR_ICON_TRANS	0x11 	// TRANS Icon
#define ADDR_ICON_MAIL	0x20 	// MAIL Icon
#define ADDR_ICON_RATE	0x0B 	// RATE Icon
#define ADDR_ICON_TITLE	0x0E 	// TITLE Icon
#define ADDR_ICON_CHP	0x08 	// CHP Icon
#define ADDR_ICON_TRK	0x05 	// TRK Icon
#define ADDR_ICON_CH	0x02 	// CH Icon
#define ADDR_ICON_HDD	0x19 	// HDD-REC
#define ADDR_ICON_DVD	0x19 	// DVD REC
#define ADDR_ICON_NWORK	0x1E 	// NETWORK Icon
#define ADDR_ICON_MUSIC	0x1F 	// MUSIC Icon
#define ADDR_ICON_USB	0x1D 	// USB Icon

#define ADDR_NETWORK_TOP 0x1F 	// NETWORK TOP
#define ADDR_NETWORK_BOT 0x1E 	// NETWORK BOTTOM

#define ADDR_BLOCKS_TOP 0x1C 	// BLOCKS TOP
#define ADDR_BLOCKS_BOT 0x1B 	// BLOCKS BOTTOM

#define ADDR_DISC_DOTS 0x19 	// Red dots
#define ADDR_DISC_SPINNER 0x18 	// DISC SPINNER

class M11BT222A
{
	private:
		uint8_t en_pin, din_pin, clk_pin, stb_pin;
		
		uint8_t brightnessRam;
		uint8_t digitRam[8];
		uint8_t recRam;
		uint16_t networkRam;
		uint16_t blocksRam;
		uint8_t dotsRam;
		uint8_t discRam;
		
		// Table for all the hexidecimal digits
		const uint8_t digitData[16] = {
		0x77, 0x12, 0x6B, 0x5B, 0x1E, 0x5D, 0x7D, 0x13, 0x7F, 0x5F, 0x3F, 0x7C, 0x65, 0x7A, 0x6D, 0x2D };

		// ASCII Table with 15 segment display characters, skipped the first 32 entries to make the table smaller
		const uint16_t charData[96] = {
			0x0000,	0x1002,	0x1400,	0xD453,	0xE553,	0x0000,	0x0000,	0x0800,	0x0820,	0x0208,	0xCE39,	0xC411,	0X0008,	0xC001,	0x0000,	0x8808,
			0xB94E,	0x1802,	0xD145,	0xD143,	0xF003,	0xA161,	0xE147,	0x1102,	0xF147,	0xF143,	0x0410,	0x0408,	0x8820,	0xC041,	0x8208,	0x5110,
			0x7544,	0xF107,	0xD552,	0x2144,	0x9552,	0xA145,	0xA105,	0xE146,	0xF007,	0x8550,	0x1046,	0xA825,	0x2044,	0xBA06,	0xB226,	0x3146,
			0xF105,	0x3166,	0xF125,	0xE143,	0x8510,	0x3046,	0xA80C,	0xB02E,	0x8A28,	0xF043,	0x8948,	0x2144,	0x8220,	0x1142,	0x8028,	0x0040,
			0x0200,	0xF107,	0xD552,	0x2144,	0x9552,	0xA145,	0xA105,	0xE146,	0xF007,	0x8550,	0x1046,	0xA825,	0x2044,	0xBA06,	0xB226,	0x3146,
			0xF105,	0x3166,	0xF125,	0xE143,	0x8510,	0x3046,	0xA80C,	0xB02E,	0x8A28,	0xF043,	0x8948,	0x0000,	0x8410,	0x0000,	0xD005,	0xBB6E };
		
		void writeData(uint8_t data);
		void writeCommand(uint8_t cmd);
		void writeMemory(uint8_t mem);
		void writeDisplayRam(uint8_t addr, uint8_t data);
	
	public:
		M11BT222A(uint8_t enable_pin, uint8_t data_in_pin, uint8_t clock_pin, uint8_t strobe_pin);
		void initDisplay();
		void initDisplay(uint8_t brightness);
		void clearDisplay();
		void setBrightness(uint8_t brightness);
		void toggleDisplay(bool show);
		
		// 7 SEGMENT FUNCTIONS
		void showNumbers(uint8_t val, uint8_t val1, uint8_t val2, uint8_t val3, uint8_t val4, uint8_t val5, bool colon1, bool colon2);
		void showNumbers(uint8_t val, uint8_t val1, uint8_t val2, uint8_t val3, uint8_t val4, uint8_t val5);
		void showNumber(uint8_t seg, uint8_t val);
		void hideNumber(uint8_t seg);
		void showNumberCustom(uint8_t seg, uint8_t data);
		void showColons(bool colon1, bool colon2, bool colon3, bool colon4);
		void showColon(uint8_t index, bool visible);
		
		// 15 SEGMENT FUNCTIONS
		void showCharacter(uint8_t seg, char character);
		void showCharacter(uint8_t seg, uint8_t character);
		void hideCharacter(uint8_t seg);
		void showCharacterCustom(uint8_t seg, uint16_t data);
		
		// ICON FUNCTIONS
		void showIconAuto(bool visible);
		void showIconEpg(bool visible);
		void showIconTrans(bool visible);
		void showIconMail(bool visible);
		void showIconRate(bool visible);
		void showIconTitle(bool visible);
		void showIconChp(bool visible);
		void showIconTrk(bool visible);
		void showIconCh(bool visible);
		void showIconHdd(bool visible);
		void showIconHddRec(bool visible);
		void showIconDvd(bool visible);
		void showIconDvdRec(bool visible);
		void showIconNetwork(bool visible);
		void showIconMusic(bool visible);
		void showIconUsb(bool visible);
		
		// NETWORK FUNCTIONS
		void toggleNetworkDots(uint16_t dots);
		void toggleNetworkDot(uint8_t index, bool visible);
		void clearNetworkDots();
		void updateNetworkDots();
		
		// BLOCK FUNCTIONS
		void toggleBlocks(uint16_t blocks);
		void toggleBlock(uint8_t x, uint8_t y, bool visible);
		void toggleBlock(uint8_t index, bool visible);
		void updateBlocks();
		
		// DOTS FUNCTIONS
		void toggleDots(uint8_t dots);
		void toggleDot(uint8_t index, bool visible);
		
		// DISC FUNCTIONS
		void toggleDisc(uint8_t index, bool visible);
		void toggleDisc(uint8_t disc);
};
	
#endif