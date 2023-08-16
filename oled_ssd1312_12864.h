/***************************************************
For ER-OLEDM 1.09 (128x64, SSD1312)
Connected with 4-Wire SPI Interface 
****************************************************/
  
#ifndef _oled_ssd1312_12864_H_
#define _oled_ssd1312_12864_H_

#include <Arduino.h>
#include <avr/pgmspace.h>

//#define _software_SPI

#define WIDTH 128
#define HEIGHT 64
#define PAGES HEIGHT/8

#ifdef _software_SPI
#define OLED_SDA 1
#define OLED_SCL 2
#endif

// For hardware SPI
// SDA is 1 (PB1/MISO/DO)
// SCK is 2 (PB2/SCK)

#define OLED_RST 3
#define OLED_DC  4
// CS is connected to GND with a 10K resistor.

#define SSD1312_12864_INIT_LEN   15
const uint8_t SSD1312_12864_INIT_CMD[] PROGMEM = {
  0xA8, 0x3F,       // set multiplex (HEIGHT-1): 0x3F for 128x64 
  0x22, 0x00, 0x03, // set min and max page
  0x20, 0x00,       // set horizontal memory addressing mode
  0x81, 0x01,       // set contrast default 0x80, 0x00 will set the display off
  0xDA, 0x10,       // set COM pins hardware configuration to sequential
  0x8D, 0x12,       // enable charge pump
  0xA1, 0xC0        // flip the screen, or "0xA0, 0xC8"
};

class SSD1312_12864 {
  public:
    void init();
    void SPIWrite(uint8_t data);
    void sendCommand(uint8_t cmd);
    void drawBitmap(const byte *bitmap, byte X, byte Y, uint8_t w, uint8_t h);
    void setCursorXY(byte X, byte Y);
};

extern SSD1312_12864 oled;

#endif
