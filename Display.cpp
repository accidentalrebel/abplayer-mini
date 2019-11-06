#include "Display.h"

void Display::log(char* log, bool canClear = false) {
  if ( canClear ) {
    SSD1306.ssd1306_fillscreen(0x00);
  }
  SSD1306.ssd1306_string_font6x8(log);
}

void Display::logInt(uint16_t val, bool canClear = false) {
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%u", val);
  log(buffer, canClear);
}

