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



static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };




const unsigned char whitebunny [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x03, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 
  0x00, 0x07, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x0c, 0x80, 0x01, 0x02, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x18, 0x00, 0x08, 0x80, 0x01, 0x84, 0x00, 0x00, 0x00, 0x00, 0x02, 
  0x08, 0x00, 0x10, 0x80, 0x00, 0x87, 0xe0, 0x00, 0x00, 0x00, 0x04, 0x08, 0x00, 0x10, 0x40, 0x07, 
  0x80, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x00, 0x20, 0x40, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x08, 0x0c, 0x00, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x00, 0x40, 0x40, 
  0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x07, 0xff, 0xe0, 0x40, 0x00, 0x04, 0x20, 0x00, 0x00, 
  0x00, 0x10, 0x00, 0x00, 0x3c, 0x40, 0x07, 0xc4, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x03, 
  0xa0, 0x18, 0x44, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x60, 0x00, 0x44, 0x00, 0x00, 
  0x00, 0x00, 0x27, 0x00, 0x00, 0x00, 0x30, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x60, 0x80, 0x00, 
  0x01, 0xd8, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x40, 0x70, 0x00, 0x0e, 0x08, 0x00, 0x84, 0x00, 
  0x00, 0x00, 0x00, 0x40, 0x18, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x04, 
  0x00, 0xe0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x07, 0x80, 0x04, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x80, 0x70, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0x70, 0x03, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x03, 0x80, 0x02, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x80, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x02, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x00, 0x60, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xe0, 0x00, 
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xa0, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x40, 0x01, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x03, 0x08, 
  0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x02, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x20, 0x04, 0x06, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x04, 
  0x02, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x04, 0x00, 0x00, 0x18, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 
  0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0xc0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xc0, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xf8, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char blackbunny [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x9f, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 
  0xf0, 0xff, 0xff, 0xff, 0x5f, 0xff, 0xfc, 0xff, 0xfe, 0xfd, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x6f, 
  0xff, 0xf8, 0xff, 0xfe, 0xfd, 0xff, 0xf0, 0xff, 0xff, 0xfe, 0xef, 0xff, 0xf3, 0x7f, 0xfe, 0xfd, 
  0xff, 0xf0, 0xff, 0xff, 0xfe, 0xe7, 0xff, 0xf7, 0x7f, 0xfe, 0x7b, 0xff, 0xf0, 0xff, 0xff, 0xfd, 
  0xf7, 0xff, 0xef, 0x7f, 0xff, 0x78, 0x1f, 0xf0, 0xff, 0xff, 0xfb, 0xf7, 0xff, 0xef, 0xbf, 0xf8, 
  0x7f, 0xff, 0xf0, 0xff, 0xff, 0xfb, 0xf7, 0xff, 0xdf, 0xbf, 0xe7, 0xff, 0xff, 0xf0, 0xff, 0xff, 
  0xf7, 0xf3, 0xff, 0xdf, 0xbf, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf7, 0xfb, 0xff, 0xbf, 0xbf, 
  0xff, 0xfc, 0x3f, 0xf0, 0xff, 0xff, 0xe7, 0xf8, 0x00, 0x1f, 0xbf, 0xff, 0xfb, 0xdf, 0xf0, 0xff, 
  0xff, 0xef, 0xff, 0xff, 0xc3, 0xbf, 0xf8, 0x3b, 0xff, 0xf0, 0xff, 0xff, 0xcf, 0xff, 0xff, 0xfc, 
  0x5f, 0xe7, 0xbb, 0xff, 0xf0, 0xff, 0xff, 0xd7, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xbb, 0xff, 0xf0, 
  0xff, 0xff, 0xd8, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xbb, 0xff, 0xf0, 0xff, 0xff, 0x9f, 0x7f, 0xff, 
  0xfe, 0x27, 0xff, 0xbb, 0xff, 0xf0, 0xff, 0xff, 0xbf, 0x8f, 0xff, 0xf1, 0xf7, 0xff, 0x7b, 0xff, 
  0xf0, 0xff, 0xff, 0xbf, 0xe7, 0xff, 0xcf, 0xf3, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xbf, 0xfb, 
  0xff, 0x1f, 0xfb, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x7f, 0xfc, 0xf8, 0x7f, 0xfb, 0xff, 0xff, 
  0xff, 0xf0, 0xff, 0xff, 0x7f, 0x8f, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x7f, 
  0x8f, 0xfc, 0x7f, 0xfd, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x7f, 0xff, 0xfc, 0x7f, 0xfd, 0xff, 
  0xff, 0xff, 0xf0, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 
  0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xfd, 
  0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xf0, 0xff, 
  0xff, 0x7f, 0xff, 0x9f, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x7f, 0xff, 0x1f, 0xff, 
  0xfd, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x7f, 0xff, 0x5f, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xf0, 
  0xff, 0xff, 0xbf, 0xfe, 0xef, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xbf, 0xfc, 0xf7, 
  0xff, 0xfb, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x9f, 0xfd, 0xfb, 0xff, 0xfb, 0xff, 0xff, 0xff, 
  0xf0, 0xff, 0xff, 0xdf, 0xfb, 0xf9, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xcf, 0xfb, 
  0xfd, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xef, 0xfb, 0xff, 0xff, 0xe7, 0xff, 0xff, 
  0xff, 0xf0, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf3, 
  0xff, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xf9, 0xff, 0xff, 0xff, 0x3f, 0xff, 
  0xff, 0xff, 0xf0, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 
  0xff, 0x3f, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0x8f, 0xff, 0x07, 0xff, 
  0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xf0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0
};

const unsigned char coverbunny [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xd0, 0x00, 0x00, 0x3f, 0x0f, 0xf9, 0xff, 0xff, 0x80, 0x40, 0x00, 
  0x30, 0x00, 0x00, 0xe0, 0x00, 0x03, 0xff, 0xff, 0x80, 0x70, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 
  0x03, 0xff, 0xff, 0x90, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x07, 0xff, 0xff, 0x0e, 0x03, 
  0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x07, 0xff, 0xff, 0x01, 0x00, 0xc0, 0x00, 0x00, 0x02, 0x00, 
  0x80, 0x07, 0xff, 0xfe, 0x00, 0x80, 0x60, 0x00, 0x00, 0x06, 0x01, 0x80, 0x07, 0xff, 0xfc, 0x00, 
  0x60, 0x30, 0x00, 0x00, 0x04, 0x03, 0x80, 0x01, 0xff, 0xc0, 0x00, 0x30, 0x08, 0x00, 0x00, 0x00, 
  0x02, 0x80, 0x40, 0x00, 0x00, 0x80, 0x10, 0x06, 0x00, 0x06, 0x00, 0x04, 0x81, 0x80, 0x00, 0x20, 
  0x80, 0x18, 0x01, 0x80, 0x06, 0x00, 0x08, 0x82, 0x00, 0x84, 0x20, 0x70, 0x00, 0x00, 0xc0, 0x05, 
  0x00, 0x10, 0x44, 0x00, 0x84, 0x10, 0x08, 0x0f, 0xc0, 0x00, 0x05, 0x1f, 0xff, 0x48, 0x01, 0x84, 
  0x10, 0x06, 0x30, 0x20, 0x00, 0x09, 0xe0, 0x00, 0xe0, 0x01, 0x02, 0x0c, 0x00, 0x38, 0x20, 0x00, 
  0x08, 0x80, 0x00, 0x10, 0x03, 0x02, 0x04, 0x00, 0x7c, 0x20, 0x00, 0x08, 0x00, 0x00, 0x0c, 0x06, 
  0x02, 0x04, 0x00, 0xfe, 0x20, 0x00, 0x08, 0x00, 0x00, 0x04, 0x04, 0x02, 0x02, 0x00, 0xff, 0x20, 
  0x00, 0x0d, 0xc0, 0x03, 0x82, 0x0c, 0x02, 0x02, 0x03, 0x7f, 0xa0, 0x00, 0x08, 0x3c, 0x3c, 0x02, 
  0x08, 0x02, 0x03, 0x04, 0x3f, 0xe0, 0x00, 0x30, 0x00, 0xc0, 0x02, 0x08, 0x02, 0x00, 0x04, 0x1f, 
  0xc0, 0x00, 0x20, 0x00, 0x00, 0x01, 0x08, 0x00, 0x00, 0x0f, 0x0f, 0xc0, 0x00, 0x20, 0x30, 0xe0, 
  0x01, 0x00, 0x00, 0x00, 0x0f, 0x83, 0x80, 0x00, 0x40, 0x30, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x1f, 
  0xc1, 0x00, 0x00, 0x40, 0x00, 0x00, 0x01, 0x01, 0xff, 0xfc, 0x1f, 0xe6, 0x00, 0x00, 0x40, 0x00, 
  0x00, 0x01, 0x0e, 0x00, 0x03, 0xef, 0xf8, 0x00, 0x00, 0x40, 0x00, 0x10, 0x02, 0xf0, 0x00, 0x00, 
  0x1f, 0xe0, 0x00, 0x00, 0x40, 0x20, 0x10, 0x03, 0x80, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x60, 
  0x20, 0x10, 0x03, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x20, 0x20, 0x10, 0x02, 0x00, 0x00, 
  0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x10, 0x30, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
  0x30, 0x08, 0x20, 0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 0x0f, 0xc0, 0x06, 0x00, 
  0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 
  0x00, 0x0c, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x34, 
  0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x01, 0xc4, 0x00, 0x00, 0x00, 0x02, 0x00, 
  0x00, 0x00, 0x00, 0x07, 0xfe, 0x04, 0x0f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x04, 0x09, 0xfc, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x08, 0x03, 0xfc, 0x06, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x08, 0x00, 0x06, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0x08, 0x00, 0x03, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x88, 0x00, 0x00, 
  0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char bunnycount3 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xfc, 
  0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x60, 0x00, 0x00, 
  0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x10, 0x0f, 0xe0, 0x00, 
  0x04, 0x00, 0x00, 0x60, 0x01, 0x00, 0x00, 0x10, 0x00, 0x1c, 0x00, 0x04, 0x00, 0x00, 0x90, 0x03, 
  0x00, 0x00, 0x10, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x90, 0x02, 0x80, 0x00, 0x10, 0x00, 0x04, 
  0x00, 0x04, 0x00, 0x01, 0x08, 0x04, 0x80, 0x00, 0x10, 0x00, 0x08, 0x00, 0x04, 0x00, 0x01, 0x08, 
  0x04, 0xc0, 0x00, 0x10, 0x00, 0xf0, 0x00, 0x04, 0x00, 0x01, 0x0f, 0xfc, 0x40, 0x00, 0x10, 0x03, 
  0xe0, 0x00, 0x04, 0x00, 0x01, 0x80, 0x07, 0xc0, 0x00, 0x10, 0x00, 0x1c, 0x00, 0x04, 0x00, 0x01, 
  0x00, 0x00, 0x70, 0x00, 0x10, 0x00, 0x04, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x0c, 0x00, 0x10, 
  0x00, 0x04, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x06, 0x00, 0x10, 0x00, 0x02, 0x00, 0x04, 0x00, 
  0x06, 0x00, 0x00, 0x02, 0x00, 0x10, 0x00, 0x06, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 
  0x10, 0x00, 0x08, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x38, 0x00, 0x04, 
  0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x10, 0x07, 0xe0, 0x00, 0x04, 0x00, 0x13, 0xfc, 0x1f, 0xf8, 
  0x80, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x10, 0x1c, 0x00, 0x38, 0x80, 0x10, 0x00, 0x00, 0x00, 
  0x04, 0x00, 0x10, 0x1c, 0x00, 0x38, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x10, 0x00, 0x00, 
  0x00, 0x80, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x80, 0x30, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x80, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 
  0x00, 0x80, 0x80, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x03, 0x80, 0x80, 0x68, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0x06, 0x00, 0x81, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 
  0x30, 0x04, 0x01, 0x07, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x1c, 0x18, 0x01, 0x0c, 0x18, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x07, 0x30, 0x01, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x10, 0x01, 0xf0, 0x03, 0xc0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xc0, 0x02, 0x00, 
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0c, 0x00, 0x00, 0x08, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x10, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x20, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x04, 0xe0, 0x00, 0xc0, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1f, 0x07, 
  0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0xf8, 0x00, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 
  0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 
  0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char bunnycount2 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xfc, 
  0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x60, 0x00, 0x00, 
  0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x10, 0x01, 0xfc, 0x00, 
  0x04, 0x00, 0x00, 0x60, 0x01, 0x00, 0x00, 0x10, 0x06, 0x03, 0x00, 0x04, 0x00, 0x00, 0x90, 0x03, 
  0x00, 0x00, 0x10, 0x08, 0x00, 0x80, 0x04, 0x00, 0x00, 0x90, 0x02, 0x80, 0x00, 0x10, 0x08, 0x00, 
  0x80, 0x04, 0x00, 0x01, 0x08, 0x04, 0x80, 0x00, 0x10, 0x00, 0x00, 0x80, 0x04, 0x00, 0x01, 0x08, 
  0x04, 0xc0, 0x00, 0x10, 0x00, 0x01, 0x80, 0x04, 0x00, 0x01, 0x0f, 0xfc, 0x40, 0x00, 0x10, 0x00, 
  0x01, 0x00, 0x04, 0x00, 0x01, 0x80, 0x07, 0xc0, 0x00, 0x10, 0x00, 0x02, 0x00, 0x04, 0x00, 0x01, 
  0x00, 0x00, 0x70, 0x00, 0x10, 0x00, 0x04, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x0c, 0x00, 0x10, 
  0x00, 0x18, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x06, 0x00, 0x10, 0x00, 0x10, 0x00, 0x04, 0x00, 
  0x06, 0x00, 0x00, 0x02, 0x00, 0x10, 0x00, 0x20, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 
  0x10, 0x00, 0xc0, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x10, 0x03, 0x00, 0x00, 0x04, 
  0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x10, 0x06, 0x00, 0x00, 0x04, 0x00, 0x13, 0xfc, 0x1f, 0xf8, 
  0x80, 0x10, 0x0f, 0xff, 0xe0, 0x04, 0x00, 0x10, 0x1c, 0x00, 0x38, 0x80, 0x10, 0x00, 0x00, 0x00, 
  0x04, 0x00, 0x10, 0x1c, 0x00, 0x38, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x10, 0x00, 0x00, 
  0x00, 0x80, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x80, 0x30, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x80, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 
  0x00, 0x80, 0x80, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x03, 0x80, 0x80, 0x68, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0x06, 0x00, 0x81, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 
  0x30, 0x04, 0x01, 0x07, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x1c, 0x18, 0x01, 0x0c, 0x18, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x07, 0x30, 0x01, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x10, 0x01, 0xf0, 0x03, 0xc0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xc0, 0x02, 0x00, 
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0c, 0x00, 0x00, 0x08, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x10, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x20, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x04, 0xe0, 0x00, 0xc0, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1f, 0x07, 
  0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0xf8, 0x00, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 
  0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 
  0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char bunnycount1 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xfc, 
  0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x60, 0x00, 0x00, 
  0x00, 0x10, 0x00, 0x30, 0x00, 0x04, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x10, 0x00, 0xf0, 0x00, 
  0x04, 0x00, 0x00, 0x60, 0x01, 0x00, 0x00, 0x10, 0x01, 0x90, 0x00, 0x04, 0x00, 0x00, 0x90, 0x03, 
  0x00, 0x00, 0x10, 0x00, 0x10, 0x00, 0x04, 0x00, 0x00, 0x90, 0x02, 0x80, 0x00, 0x10, 0x00, 0x10, 
  0x00, 0x04, 0x00, 0x01, 0x08, 0x04, 0x80, 0x00, 0x10, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x08, 
  0x04, 0xc0, 0x00, 0x10, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x0f, 0xfc, 0x40, 0x00, 0x10, 0x00, 
  0x10, 0x00, 0x04, 0x00, 0x01, 0x80, 0x07, 0xc0, 0x00, 0x10, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 
  0x00, 0x00, 0x70, 0x00, 0x10, 0x00, 0x10, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x0c, 0x00, 0x10, 
  0x00, 0x10, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x06, 0x00, 0x10, 0x00, 0x10, 0x00, 0x04, 0x00, 
  0x06, 0x00, 0x00, 0x02, 0x00, 0x10, 0x00, 0x10, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 
  0x10, 0x00, 0x10, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x10, 0x00, 0x04, 
  0x00, 0x08, 0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x10, 0x00, 0x04, 0x00, 0x13, 0xfc, 0x1f, 0xf8, 
  0x80, 0x10, 0x03, 0xff, 0x80, 0x04, 0x00, 0x10, 0x1c, 0x00, 0x38, 0x80, 0x10, 0x00, 0x00, 0x00, 
  0x04, 0x00, 0x10, 0x1c, 0x00, 0x38, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x10, 0x00, 0x00, 
  0x00, 0x80, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x80, 0x30, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x80, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 
  0x00, 0x80, 0x80, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x03, 0x80, 0x80, 0x68, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0x06, 0x00, 0x81, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 
  0x30, 0x04, 0x01, 0x07, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x1c, 0x18, 0x01, 0x0c, 0x18, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x07, 0x30, 0x01, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x10, 0x01, 0xf0, 0x03, 0xc0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xc0, 0x02, 0x00, 
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0c, 0x00, 0x00, 0x08, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x10, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x20, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x04, 0xe0, 0x00, 0xc0, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1f, 0x07, 
  0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0xf8, 0x00, 0x40, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 
  0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 
  0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

int minutes = 0;
int seconds = 3; 


void setup()   {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  analogWrite(9, 255);
  display.begin();
  // init done
  
  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(50);
  display.clearDisplay();
  display.drawBitmap(0, 0,  coverbunny, 84, 48, 1);
  display.display();
  delay(3000);

  display.clearDisplay();
  display.setCursor(10 ,5);
  display.setTextSize(1);
  display.println("SHOWER TIME");
  display.setCursor(12, 25);
  display.setTextSize(2); 
  display.print(minutes); 
  display.print(" MIN");
  display.display();
  delay(1500);

  display.clearDisplay();
  display.drawBitmap(0, 0,  bunnycount3, 84, 48, 1);
  display.display();
  delay(1000);

  display.clearDisplay();
  display.drawBitmap(0, 0,  bunnycount2, 84, 48, 1);
  display.display();
  delay(1000);
  
  display.clearDisplay();
  display.drawBitmap(0, 0,  bunnycount1, 84, 48, 1);
  display.display();
  delay(1000);
  
}

void loop() {
  if (minutes == 0 && seconds == 0){ 
    display.clearDisplay();
    display.drawBitmap(0, 0,  whitebunny, 84, 48, 1);
    display.display();
    delay(1000);
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(5,10);
    display.println("GET");
    display.setCursor(40, 30);
    display.println("OUT");
    display.display();
    delay(1000);
    display.clearDisplay();
    display.drawBitmap(0, 0,  blackbunny, 84, 48, 1);
    display.display();
    delay(1000);
  } else {
    if (seconds == 0) {
    minutes--; 
    seconds = 59;
    } else {
    seconds--; 
    }
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextSize(2);
    display.setCursor(12,15);
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

  

}
