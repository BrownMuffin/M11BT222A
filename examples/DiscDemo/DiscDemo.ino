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
  // Single disc element spinning
  for (unsigned char i = 0; i < 2; i++)
  {
    for (unsigned char j = 0; j < 8; j++)
    {
      // Turn element with index 'j' on
      screen.toggleDisc(j, true);
      // Turn element with index 'j - 1' off (or index 7 if 'j' is 0)
      screen.toggleDisc((j > 0) ? j - 1 : 7, false);
      delay(100);
    }
  }

  screen.clearDisplay();
  delay(500);

  // Double disc element spinning
  for (unsigned char i = 0; i < 4; i++)
  {
    for (unsigned char j = 0; j < 4; j++)
    {
      // Turn elements on, by bit shifting you move the elements
      unsigned char disc = 0x11;
      screen.toggleDisc(disc << j);
      
      delay(100);
    }
  }

  screen.clearDisplay();
  delay(500);

  // Inverted double disc element spinning
  for (unsigned char i = 0; i < 4; i++)
  {
    for (unsigned char j = 0; j < 4; j++)
    {
      // Turn elements on, by bit shifting you move the elements
      // The ~ is bitwise NOT, and inverting the bits. Resulting in two elements that are off and the rest on.
      unsigned char disc = 0x11;
      screen.toggleDisc(~(disc << j));
      
      delay(100);
    }
  }

  screen.clearDisplay();
  delay(500);
}
