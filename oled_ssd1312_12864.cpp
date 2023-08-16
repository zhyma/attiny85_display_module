/***************************************************
For ER-OLEDM 1.09 (128x64, SSD1312)
Connected with 4-Wire SPI Interface 
****************************************************/
#include "tinySPI.h"
#include "oled_ssd1312_12864.h"

#include <Arduino.h>
#include <avr/pgmspace.h>

void SSD1312_12864::sendCommand(uint8_t cmd){
  digitalWrite(OLED_DC, LOW);
  SPIWrite(cmd);
  digitalWrite(OLED_DC, HIGH);
}

void SSD1312_12864::SPIWrite(uint8_t data) {
  #ifdef _software_SPI
    shiftOut(OLED_SDA, OLED_SCL, MSBFIRST, data);
  #else
    SPI.transfer(data);
  #endif
}

void SSD1312_12864::init()
{
    #ifdef _software_SPI
    pinMode(OLED_SDA, OUTPUT);
    pinMode(OLED_SCL, OUTPUT);
    #endif
    
    pinMode(OLED_RST, OUTPUT);
    pinMode(OLED_DC, OUTPUT);
    digitalWrite(OLED_DC, HIGH);
    #ifndef _software_SPI
      SPI.begin();
    #endif

    digitalWrite(OLED_RST, HIGH);
    delay(10);
    digitalWrite(OLED_RST, LOW);
    delay(10);
    digitalWrite(OLED_RST, HIGH);
    delay(100);

    for (uint8_t i = 0; i < SSD1312_12864_INIT_LEN; i++){
      sendCommand(pgm_read_byte(&SSD1312_12864_INIT_CMD[i]));
    }

    oled.drawBitmap(NULL, 0, 0, 128, 8);
    delay(100);
    sendCommand(0xAF);

    delay(100);
}


void SSD1312_12864::setCursorXY(byte X, byte Y){
  // Y up to down,    unit: 1 page (8 pixels)
  // X left to right, unit: 1 seg  (1 pixel)
    sendCommand(0xB0 + Y);/* set page address */     
    sendCommand(0x00 + (X & 0x0F));   /* set low column address */      
    sendCommand(0x10 + ((X>>4)&0x0F));  /* set high column address */    
}

void SSD1312_12864::drawBitmap(const byte *bitmap, byte X, byte Y, uint8_t w, uint8_t h)
{
  setCursorXY(X, Y);
  digitalWrite(OLED_DC, HIGH);
  for (uint8_t i = 0; i < h; i++) {         
          
      for(uint8_t j = 0; j< w; j++ ) {
        if (bitmap==NULL)
          SPIWrite(0); // clear area
        else
          SPIWrite(pgm_read_byte(&bitmap[i*w+j]));
      }
      setCursorXY(X, ++Y);
  }
}

SSD1312_12864 oled;  // Preinstantiate Objects
