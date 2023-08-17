/***************************************************
For ER-OLEDM 1.09 (128x64, SSD1312)
Connected with 4-Wire SPI Interface 
****************************************************/
  
#ifndef _oled_ssd1306s_H_
#define _oled_ssd1306s_H_

#include <Arduino.h>
#include <avr/pgmspace.h>

/**** Use software SPI****/
//#define _software_SPI
/**** Driver: SSD1312, OLED size: 128x64 ****/
//#define _oled_ssd1312_12864_H_
/**** Driver: CH1115, OLED size: 128x64 ****/
//#define _oled_ch1115_12864_H_
/**** Driver: SSD1306, OLED size: 128x32 ****/
//#define _oled_ssd1306_12832_H_
/**** Driver: SSD1306, OLED size: 72x40 ****/
#define _oled_ssd1306_7240_H_

#ifdef _software_SPI
#define OLED_SDA 1
#define OLED_SCL 2
#endif

#if defined(_oled_ssd1312_12864_H_) || defined(_oled_ch1115_12864_H_)
// For hardware SPI: SDA is 1 (PB1/MISO/DO), SCK is 2 (PB2/SCK)
#define OLED_RST 3
#define OLED_DC  4
// CS is connected to GND with a 10K resistor.
#define WIDTH 128
#define HEIGHT 64
#endif

#if defined(_oled_ssd1306_12832_H_)
#define OLED_ADDRESS      0x3C
#define OLED_COMMAND_MODE 0x00//0x80 (0x00?0x80? both works?)
#define OLED_DATA_MODE    0x40
#define WIDTH 128
#define HEIGHT 32
#endif


#if defined(_oled_ssd1306_7240_H_)
#define OLED_ADDRESS      0x3C
#define OLED_COMMAND_MODE 0x00
#define OLED_DATA_MODE    0x40
#define WIDTH  72
#define HEIGHT 40
#endif

#define PAGES HEIGHT/8

#ifdef _oled_ssd1312_12864_H_
#define OLED_INIT_LEN   15
const uint8_t OLED_INIT_CMD[] PROGMEM = {
  0xA8, 0x3F,       // set multiplex (HEIGHT-1): 0x3F for 128x64 
  0x22, 0x00, 0x03, // set min and max page
  0x20, 0x00,       // set horizontal memory addressing mode
  0x81, 0x01,       // set contrast default 0x80, 0x00 will set the display off
  0xDA, 0x10,       // set COM pins hardware configuration to sequential
  0x8D, 0x12,       // enable charge pump
  0xA1, 0xC0        // flip the screen, or "0xA0, 0xC8"
};
#endif

#ifdef _oled_ch1115_12864_H_
#define OLED_INIT_LEN   28
const uint8_t OLED_INIT_CMD[] PROGMEM = {
  0xAE,             // display off
  0x00, 0x10, 0xB0, // set lower column address, higher column address, and page address
  0x40,             //set display start lines
  0x81, 0x01,       //contract control, default 0x80
  0x82, 0x00,       //iref resistor set and adjust ISEG
  0xA0,             // set segment remap 0xA0
  0xA2,             // set seg pads hardware configuration
  0xA4,             // disable entire display on (0xA4, 0xA5)
  0xA6,             // normal (0xA7 is reverse)
  0xA8,             // multiplex ratio
  0x3F,             // duty = 1/64
  0xC0,             // Com scan direction 0xC0
  0xD3, 0x00,       // set display offset
  0xD5, 0xA0,       // set osc division
  0xD9, 0x22,       // set pre-charge period
  0xDB, 0x40,       // set vcomh
  0x31,             // set pump 7.4v
  0xAD,             // set charge pump enable
  0x8B,             // set dc-dc enable (0x8A=disable; 0x8B=enable)
};
#endif

#ifdef _oled_ssd1306_12832_H_
#define OLED_INIT_LEN   13
const uint8_t OLED_INIT_CMD[] PROGMEM = {
  0xA8, 0x1F,       // set multiplex (HEIGHT-1): 0x1F for 128x32, 0x3F for 128x64 
  0x22, 0x00, 0x03, // set min and max page
  0x20, 0x00,       // set horizontal memory addressing mode
  0x81, 0x01,       // set contrast default 0x80, you can set it to 0x00 without turning it off
  0xDA, 0x02,       // set COM pins hardware configuration to sequential
  0x8D, 0x14       // enable charge pump
  //0xA1, 0xC8        // flip the screen
};
#endif

#ifdef _oled_ssd1306_7240_H_
#define OLED_INIT_LEN   24
const uint8_t OLED_INIT_CMD[] PROGMEM = {
  0xAE,//--turn off oled panel
  0xD5, 0x80,//--set display clock divide ratio/oscillator frequency --set divide ratio
  0xA8, 0x27,//--set multiplex ratio --1/40 duty
  0xD3, 0x00,//-set display offset-not offset
  0xAD, 0x30,//--Internal IREF Setting 
  0x8D, 0x14,//--set Charge Pump enable/disable--set(0x10) disable
  0x40,//--set start line address
  0xA6,//--set normal display
  0xA4,//Disable Entire Display On
  0xA1,//--set segment re-map 128 to 0
  0xC8,//--Set COM Output Scan Direction 64 to 0
  0xDA, 0x12,//--set com pins hardware configuration
  0x81, 0x00,//--set contrast control register
  0xD9, 0x22,//--set pre-charge period
  0xDB, 0x20//--set vcomh
};
#endif

class SSD1306s {
  public:
    void init();
    void sendData(uint8_t data);
    void sendCommand(uint8_t cmd);
    void drawBitmap(const byte *bitmap, byte X, byte Y, uint8_t w, uint8_t h);
    void setCursorXY(byte X, byte Y);
};

extern SSD1306s oled;

#endif
