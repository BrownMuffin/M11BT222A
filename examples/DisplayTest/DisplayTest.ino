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

void loop()
{
  // Loop through numbers
  for (unsigned char i = 0; i < 16; i++)
  {
    screen.showNumbers(i, i, i, i, i, i, false, false);
    delay(250);
    screen.showNumbers(i, i, i, i, i, i, true, true);
    delay(250);
  }

  screen.clearDisplay();
  delay(500);
  
  // Loop through text
  for (unsigned int j = 32; j < 128; j++)
  {
    screen.showCharacter(0, j);
    screen.showCharacter(1, j);
    screen.showCharacter(2, j);
    screen.showCharacter(3, j);
    screen.showCharacter(4, j);
    
    delay(200);
  }
  
  screen.clearDisplay();
  delay(500);
  
  // Loop through icons
  screen.showIconAuto(true);
  delay(500);
  screen.showIconAuto(false);
  screen.showIconEpg(true);
  delay(500);
  screen.showIconEpg(false);
  screen.showIconTrans(true);
  delay(500);
  screen.showIconTrans(false);
  screen.showIconMail(true);
  delay(500);
  screen.showIconMail(false);
  screen.showIconRate(true);
  delay(500);
  screen.showIconRate(false);
  screen.showIconTitle(true);
  delay(500);
  screen.showIconTitle(false);
  screen.showIconChp(true);
  delay(500);
  screen.showIconChp(false);
  screen.showIconTrk(true);
  delay(500);
  screen.showIconTrk(false);
  screen.showIconCh(true);
  delay(500);
  screen.showIconCh(false);
  
  screen.clearDisplay();

  delay(1000);
}