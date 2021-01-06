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
  
  // Dot example
  screen.toggleDot(0, true);
  delay(200);
  
  screen.toggleDot(0, false);
  screen.toggleDot(1, true);
  delay(200);
  
  screen.toggleDot(1, false);
  screen.toggleDot(2, true);
  delay(200);
  
  screen.toggleDot(2, false); 
  screen.toggleDot(3, true);
  delay(200);
  
  screen.toggleDot(3, false); 

  delay(1000);

  // Dots example
  screen.toggleDots(0x08); // 1000
  delay(200);
  
  screen.toggleDots(0x04); // 0100
  delay(200);
  
  screen.toggleDots(0x02); // 0010
  delay(200);
  
  screen.toggleDots(0x01); // 0001
  delay(200);

  screen.toggleDots(0x00); // 0000
  delay(1000);

}
