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
  
  // Loop through all the icons
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
  screen.showIconHdd(true);
  delay(500);
  screen.showIconHdd(false);
  screen.showIconHddRec(true);
  delay(500);
  screen.showIconHddRec(false);
  screen.showIconDvd(true);
  delay(500);
  screen.showIconDvd(false);
  screen.showIconDvdRec(true);
  delay(500);
  screen.showIconDvdRec(false);
  screen.showIconNetwork(true);
  delay(500);
  screen.showIconNetwork(false);
  screen.showIconMusic(true);
  delay(500);
  screen.showIconMusic(false);
  screen.showIconUsb(true);
  delay(500);
  screen.showIconUsb(false);
  
  delay(500);
}
