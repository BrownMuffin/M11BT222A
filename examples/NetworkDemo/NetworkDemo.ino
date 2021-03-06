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
  for (uint8_t i = 0; i < 5; i++)
  {
    // Turn on dot with index 0
    screen.toggleNetworkDot(0, true);
    // Draw the dots on the display
    screen.updateNetworkDots();
    delay(100);
    
    // Turn off dot with index 0
    screen.toggleNetworkDot(0, false);
    // Turn on dot with index 1
    screen.toggleNetworkDot(1, true);
    // Draw the dots on the display
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
  for (uint8_t i = 0; i < 5; i++)
  {
    for (uint8_t j = 0; j < 7; j++)
    {
      // Turn off all the network dots
      screen.clearNetworkDots();

      // Enable dots from the top and bottom half
      screen.toggleNetworkDot(j, true);
      screen.toggleNetworkDot(j + 7, true);

      // Draw the dots on the display
      screen.updateNetworkDots();
      delay(100);
    }
    delay(200);
  }

  screen.clearDisplay();
  delay(1000);
}