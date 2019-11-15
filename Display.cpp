#include "Display.h"

bool Display::isTurnedOn = false;

void Display::init() {
  SSD1306.ssd1306_init();
  SSD1306.ssd1306_fillscreen(0x00);

  SSD1306.ssd1306_setpos(3, 0);
  SSD1306.ssd1306_string_font6x8("ABPlayer Mini");
  SSD1306.ssd1306_setpos(3, 1);
  SSD1306.ssd1306_string_font6x8("Ver 1.0");

  isTurnedOn = true;
}

void Display::sleep() {
  if ( !isTurnedOn ) {
    return;
  }

  isTurnedOn = false;
  SSD1306.ssd1306_send_command(0xAE);
}

void Display::wake() {
  if ( isTurnedOn ) {
    return;
  }

  isTurnedOn = true;
  SSD1306.ssd1306_send_command(0xAF);
}

void Display::onUpdateCurrentPlayed() {
  
}

void Display::onUpdatedVolume(uint16_t vol) {
  SSD1306.ssd1306_setpos(5, 4);

  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%u", vol);
  SSD1306.ssd1306_string_font6x8(buffer);
}

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
