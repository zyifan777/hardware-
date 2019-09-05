/*********************************************************************
This is an example sketch for our Monochrome Nokia 5110 LCD Displays

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/338

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Software SPI (slower updates, more flexible pin options):
// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 5, 7, 6);

// Hardware SPI (faster, but must use certain hardware pins):
// SCK is LCD serial clock (SCLK) - this is pin 13 on Arduino Uno
// MOSI is LCD DIN - this is pin 11 on an Arduino Uno
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
// Adafruit_PCD8544 display = Adafruit_PCD8544(5, 4, 3);
// Note with hardware SPI MISO and SS pins aren't used but will still be read
// and written to during SPI transfer.  Be careful sharing these pins!

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16



int minutes = 0;
int seconds = 50; 
boolean starting = true; 
void setup()   {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  analogWrite(9, 255);
  display.begin();
  // init done
  
  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(20);

  display.clearDisplay();
  display.setTextSize(2);
  display.println("CODER");
  display.print("CLOCK");
  display.display();
  delay(3000);
}

void loop() {
  if (starting) {
    display.clearDisplay();
    display.setCursor(20,8);
    display.setTextSize(2);
    display.println("WORK");
    display.setCursor(12,28);
    display.println("START!");
//    display.drawLine(0, 30, 84, 30, 1);
    display.display();
    starting = false; 
    minutes = 0;
    seconds = 50; 
    delay(1000);  
  }

  if (minutes == 1) {
    display.clearDisplay();
    display.setTextSize(2);
    display.print("Take a Break!");
    display.display();
    starting = true;
    delay(5000);
    return; 
  }

  
  display.clearDisplay();
  display.setCursor(12,15);
  seconds++;
  if (seconds == 60) {
    minutes++; 
    seconds = 0;
  }
  display.setTextSize(2);

  if (minutes < 10) {
    display.print("0");
  }
  display.print(minutes);
  display.print(":");
  if (seconds < 10) {
    display.print("0");
  }
  display.print(seconds);
  display.display();
  delay(1000);  
}
