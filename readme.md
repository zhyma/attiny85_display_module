- A very simplified library for ATtiny85 to communicate with OLED screens driven by SSD1306 series chips (SSD1306, CH1115, SSD1312)

- Currently tested:
  - MCU: Adafruit Trinket (ATtiny85@8MHz, 3.3V version)
  - OLED:
    - CH1115, 1.09in, 128x64, SPI (https://www.buydisplay.com/spi-white-1-09-inch-oled-display-module-64x128-arduino-raspberry-pi)
    - SSD1312, 1.09in, 128x64, SPI (https://www.buydisplay.com/spi-white-1-09-inch-oled-display-module-64x128-arduino-raspberry-pi)

- Usage:
  In `oled_ssd1306s.h`
  - Select the screen type (`_oled_ssd1312_12864_H_`, `_oled_ch1115_12864_H_`) by using `#define`
  - Select the interface `_software_SPI`