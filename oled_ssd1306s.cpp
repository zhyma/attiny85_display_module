/***************************************************
For ER-OLEDM 1.09 (128x64, SSD1312)
Connected with 4-Wire SPI Interface 
****************************************************/
#include "oled_ssd1306s.h"

#if defined(_oled_ssd1312_12864_H_) || defined(_oled_ch1115_12864_H_)
  #include "tinySPI.h"
#endif

#if defined(_oled_ssd1306_12832_H_) || defined (_oled_ssd1306_7240_H_)
  #include "TinyWireM.h"
#endif

#include <Arduino.h>
#include <avr/pgmspace.h>

void SSD1306s::sendCommand(uint8_t cmd){
  #if defined(_oled_ssd1312_12864_H_) || defined(_oled_ch1115_12864_H_)
  digitalWrite(OLED_DC, LOW);
  sendData(cmd);
  digitalWrite(OLED_DC, HIGH);
  #endif

  #if defined(_oled_ssd1306_12832_H_) || defined (_oled_ssd1306_7240_H_)
  TinyWireM.beginTransmission(OLED_ADDRESS); // begin transmitting
  TinyWireM.send(OLED_COMMAND_MODE);//data mode
  TinyWireM.send(cmd);
  TinyWireM.endTransmission();    // stop transmitting
  #endif
}

void SSD1306s::sendData(uint8_t data) {
  #ifdef _software_SPI
    shiftOut(OLED_SDA, OLED_SCL, MSBFIRST, data);
  #elif defined (_oled_ssd1312_12864_H_) || defined(_oled_ch1115_12864_H_)
    SPI.transfer(data);
  #elif defined (_oled_ssd1306_12832_H_) || defined (_oled_ssd1306_7240_H_)
    TinyWireM.beginTransmission(OLED_ADDRESS); // begin transmitting
    TinyWireM.send(OLED_DATA_MODE);//data mode
    TinyWireM.send(data);
    TinyWireM.endTransmission();    // stop transmitting
  #endif
}

void SSD1306s::init()
{
    #if defined(_oled_ssd1312_12864_H_) || defined(_oled_ch1115_12864_H_)
      #ifdef _software_SPI
      pinMode(OLED_SDA, OUTPUT);
      pinMode(OLED_SCL, OUTPUT);
      #else
      SPI.begin();
      #endif
      
      pinMode(OLED_RST, OUTPUT);
      pinMode(OLED_DC, OUTPUT);
      digitalWrite(OLED_DC, HIGH);
  
      digitalWrite(OLED_RST, HIGH);
      delay(10);
      digitalWrite(OLED_RST, LOW);
      delay(10);
      digitalWrite(OLED_RST, HIGH);
      delay(100);
    #else defined(_oled_ssd1306_12832_H_) || defined (_oled_ssd1306_7240_H_)
      TinyWireM.begin();
    #endif

    for (uint8_t i = 0; i < OLED_INIT_LEN; i++){
      sendCommand(pgm_read_byte(&OLED_INIT_CMD[i]));
    }

    oled.drawBitmap(NULL, 0, 0, WIDTH, HEIGHT);
    delay(100);
    sendCommand(0xAF);

    delay(100);
}

void SSD1306s::setCursorXY(byte X, byte Y){
  // Y up to down,    unit: 1 page (8 pixels)
  // X left to right, unit: 1 seg  (1 pixel)
  #ifdef _oled_ch1115_12864_H_
  sendCommand(0xB0 + Y);/* set page address */     
  sendCommand(0x00 + (X & 0x0F));   /* set low column address */      
  sendCommand(0x10 + ((X>>4)&0x0F));  /* set high column address */
  #endif

  #ifdef _oled_ssd1312_12864_H_
  sendCommand(0xB0 + Y);/* set page address */     
  sendCommand(0x00 + (X & 0x0F));   /* set low column address */      
  sendCommand(0x10 + ((X>>4)&0x0F));  /* set high column address */
  #endif

  #ifdef _oled_ssd1306_12832_H_
  sendCommand(0xB0 + Y);                //set page address
  sendCommand(0x00 + (X & 0x0F));     //set column lower address
  sendCommand(0x10 + ((X>>4)&0x0F));  //set column higher address
  #endif

  #ifdef _oled_ssd1306_7240_H_
  sendCommand(0xB0 + Y);                //set page address
  sendCommand(0x0c);     //set column lower address
  sendCommand(0x11);  //set column higher address
  #endif
}

void SSD1306s::drawBitmap(const byte *bitmap, byte X, byte Y, uint8_t w, uint8_t h)
{
  setCursorXY(X, Y);
  #if defined(_oled_ssd1312_12864_H_) || defined(_oled_ch1115_12864_H_)
  digitalWrite(OLED_DC, HIGH);
  #endif
  for (uint8_t i = 0; i < h; i++) {         
          
      for(uint8_t j = 0; j< w; j++ ) {
        if (bitmap==NULL)
          sendData(0); // clear area
        else
          sendData(pgm_read_byte(&bitmap[i*w+j]));
      }
      setCursorXY(X, ++Y);
  }
}

SSD1306s oled;  // Preinstantiate Objects
