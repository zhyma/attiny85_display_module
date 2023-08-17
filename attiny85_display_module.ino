/***************************************************
Tested and worked with:
Works with Arduino 1.8.13 IDE + Adafruit Trinket Attiny85@8MHz, 3.3V
****************************************************/
 
/*
  == Hardware connection ==
    OLED   =>    Arduino
  *1. GND    ->    GND
  *2. VCC    ->    3.3
  *3. SCL    ->    2
  *4. SDA    ->    1
  *5. RES    ->    3
  *6. DC     ->    4
  *7. CS     ->    10K TO GND
*/


#include "tinySPI.h"
#include "oled_ssd1306s.h"

#include "bitmap.h"

void setup() {
  oled.init();
  delay(100);
  
  delay(100);
  oled.drawBitmap(test, 0, 0, 72, 4);
}

void loop() {
}
