#include "M11BT222A.h"

#define EN_PIN 5
#define DIN_PIN 2
#define CLK_PIN 3
#define STB_PIN 4

// Declare the M11BT222A display
M11BT222A screen(EN_PIN, DIN_PIN, CLK_PIN, STB_PIN);

void setup() {
  // Initialize the display
  screen.initDisplay();
}

void loop() {
  // Loop through the digits 1 to 16 (F), showing the colons every half second
  for (unsigned char i = 0; i < 16; i++)
  {
    screen.showNumbers(i, i, i, i, i, i, false, false);
    delay(500);
    screen.showColons(true, true, true, true);
    delay(500);
  }

  screen.clearDisplay();
  delay(1000);

  // Show a custom number
  for (unsigned char i = 0; i < 6; i++)
  {
    screen.showNumberCustom(i, 0x01); // 0000 0001
    delay(100);
    screen.showNumberCustom(i, 0x03); // 0000 0011
    delay(100);
    screen.showNumberCustom(i, 0x13); // 0001 0011
    delay(100);
    screen.showNumberCustom(i, 0x53); // 0101 0011
    delay(100);
    screen.showNumberCustom(i, 0x73); // 0111 0011
    delay(100);
    screen.showNumberCustom(i, 0x77); // 0111 0111
    delay(200);
  }

  screen.clearDisplay();
  delay(1000);
}
