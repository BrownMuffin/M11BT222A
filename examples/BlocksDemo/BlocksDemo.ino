/*
 * Pin 1: +5V
 * Pin 2: GND
 * Pin 3: N/C
 * Pin 4: Enable (High turns the display on)
 * Pin 5: Data In
 * Pin 6: GND
 * Pin 7: Serial Clock (Inverted)
 * Pin 8: Serial Strobe (Inverted)
 */

#include "M11BT222A.h"

#define EN_PIN 5
#define DIN_PIN 2
#define CLK_PIN 3
#define STB_PIN 4

M11BT222A screen(EN_PIN, DIN_PIN, CLK_PIN, STB_PIN);

void setup() {
  screen.initDisplay();
}

void loop() {
  screen.clearDisplay();
  
  // Setting blocks by x and y coordinates
  screen.toggleBlock(0, 0, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(1, 0, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(2, 0, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(3, 0, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(3, 1, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(2, 1, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(1, 1, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0, 1, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0, 2, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(1, 2, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(2, 2, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(3, 2, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(3, 3, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(2, 3, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(1, 3, true);
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0, 3, true);
  screen.updateBlocks();
  delay(1000);

  // Setting blocks by index
  screen.toggleBlock(0x0F, false); // 16
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x0B, false); // 11
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x07, false); // 7
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x03, false); // 3
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x02, false); // 2
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x06, false); // 6
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x0A, false); // 10
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x0E, false); // 14
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x0D, false); // 13
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x09, false); // 9
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x05, false); // 5
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x01, false); // 1
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x00, false); // 0
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x04, false); // 4
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x08, false); // 8 
  screen.updateBlocks();
  delay(100);
  
  screen.toggleBlock(0x0C, false); // 12
  screen.updateBlocks();
  delay(1000);

  // Settings all the blocks with one int
  for (unsigned char i = 0; i < 5; i++)
  {
    screen.toggleBlocks(0xA5A5); // 1010 1010 1010 1010
    screen.updateBlocks();
    delay(500);
    screen.toggleBlocks(0x5A5A); // 0101 0101 0101 0101
    screen.updateBlocks();
    delay(500);
  }
  
  screen.clearDisplay();
  delay(1000);
 
  // Settings all the blocks based on a random int
  for (unsigned char i = 0; i < 40; i++)
  {
    screen.toggleBlocks(random(65536));
    screen.updateBlocks();
    delay(50);
  }

  delay(1000);
}
