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
  screen.clearDisplay();

  // Single dot
  for (unsigned char i = 0; i < 5; i++)
  {
    screen.toggleNetworkDot(0, true);
    screen.updateNetworkDots();
    delay(100);
    screen.toggleNetworkDot(0, false);
    screen.toggleNetworkDot(1, true);
    screen.updateNetworkDots();
    delay(100);
    screen.toggleNetworkDot(1, false);
    screen.toggleNetworkDot(2, true);
    screen.updateNetworkDots();
    delay(100);
    screen.toggleNetworkDot(2, false); 
    screen.toggleNetworkDot(3, true);
    screen.updateNetworkDots();
    delay(100);
    screen.toggleNetworkDot(3, false); 
    screen.toggleNetworkDot(4, true);
    screen.updateNetworkDots();
    delay(100);
    screen.toggleNetworkDot(4, false); 
    screen.toggleNetworkDot(5, true);
    screen.updateNetworkDots();
    delay(100);
    screen.toggleNetworkDot(5, false); 
    screen.toggleNetworkDot(6, true);
    screen.updateNetworkDots();
    delay(300);
    screen.toggleNetworkDot(6, false); 
    screen.toggleNetworkDot(7, true);
    screen.updateNetworkDots();
    delay(100);
    screen.toggleNetworkDot(7, false); 
    screen.toggleNetworkDot(8, true);
    screen.updateNetworkDots();
    delay(100);
    screen.toggleNetworkDot(8, false); 
    screen.toggleNetworkDot(9, true);
    screen.updateNetworkDots();
    delay(100);
    screen.toggleNetworkDot(9, false); 
    screen.toggleNetworkDot(10, true);
    screen.updateNetworkDots();
    delay(100);
    screen.toggleNetworkDot(10, false); 
    screen.toggleNetworkDot(11, true);
    screen.updateNetworkDots();
    delay(100);
    screen.toggleNetworkDot(11, false); 
    screen.toggleNetworkDot(12, true);
    screen.updateNetworkDots();
    delay(100);
    screen.toggleNetworkDot(12, false); 
    screen.toggleNetworkDot(13, true);
    screen.updateNetworkDots();
    delay(300);
    screen.toggleNetworkDot(13, false); 
    screen.updateNetworkDots();
  }

  screen.clearDisplay();
  delay(1000);
  
  // Double dot
  for (unsigned char i = 0; i < 5; i++)
  {
    screen.clearNetworkDots();
    screen.toggleNetworkDot(0, true);
    screen.toggleNetworkDot(7, true);
    screen.updateNetworkDots();
    delay(100);
    screen.clearNetworkDots();
    screen.toggleNetworkDot(1, true);
    screen.toggleNetworkDot(8, true);
    screen.updateNetworkDots();
    delay(100);
    screen.clearNetworkDots();
    screen.toggleNetworkDot(2, true);
    screen.toggleNetworkDot(9, true);
    screen.updateNetworkDots();
    delay(100);
    screen.clearNetworkDots();
    screen.toggleNetworkDot(3, true);
    screen.toggleNetworkDot(10, true);
    screen.updateNetworkDots();
    delay(100);
    screen.clearNetworkDots();
    screen.toggleNetworkDot(4, true);
    screen.toggleNetworkDot(11, true);
    screen.updateNetworkDots();
    delay(100);
    screen.clearNetworkDots();
    screen.toggleNetworkDot(5, true);
    screen.toggleNetworkDot(12, true);
    screen.updateNetworkDots();
    delay(100);
    screen.clearNetworkDots();
    screen.toggleNetworkDot(6, true);
    screen.toggleNetworkDot(13, true);
    screen.updateNetworkDots();
    delay(300);
  }

  screen.clearDisplay();
  delay(1000);
}
