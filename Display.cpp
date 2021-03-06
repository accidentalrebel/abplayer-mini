#include "Display.h"

bool Display::isTurnedOn = false;

void Display::init() {
  ssd1306_init();
  ssd1306tx_init(ssd1306xled_font6x8data, ' ');
  ssd1306_clear();

  ssd1306_setpos(3, 0);
  ssd1306tx_string("ABPlayer Mini");
  ssd1306_setpos(3, 1);
  ssd1306tx_string("Ver 1.0");

  isTurnedOn = true;
}

void Display::sleep() {
  if ( !isTurnedOn ) {
    return;
  }

  isTurnedOn = false;
  ssd1306_start_command();
  ssd1306_data_byte(0xAE);
  ssd1306_stop();
}

void Display::wake() {
  if ( isTurnedOn ) {
    return;
  }

  isTurnedOn = true;
  ssd1306_start_command();
  ssd1306_data_byte(0xAF);
  ssd1306_stop();
}

void Display::setupMessage(bool canClear) {
  if ( canClear ) {
    clearLine(7);
    ssd1306_setpos(5, 7);
  }
}

void Display::onUpdateMessage(char* message, bool canClear = false) {
  setupMessage(canClear);
  ssd1306tx_string(message);
}

void Display::onUpdatedMode(char* mode) {
  clearLine(2);
  ssd1306_setpos(5, 2);
  ssd1306tx_string(mode);
}

void Display::onUpdateMessageNum(uint16_t num, bool canClear = false) {
  setupMessage(canClear);
  ssd1306tx_numdec(num);
}

void Display::onUpdateCurrentPlayed(uint16_t trackNum, uint16_t maxNum) {
  ssd1306_setpos(5, 3);
  ssd1306tx_numdec(trackNum);
  ssd1306tx_string("/");
  ssd1306tx_numdec(maxNum);
}

void Display::onUpdatedVolume(uint16_t vol) {
  ssd1306_setpos(5, 4);
  ssd1306tx_numdec(vol);
  ssd1306tx_string("/30");
}

void Display::log(char* log, bool canClear = false) {
  if ( canClear ) {
    ssd1306_clear();
  }
  ssd1306tx_string(log);
}

void Display::logInt(uint16_t val, bool canClear = false) {
  ssd1306tx_numdec(val);
}

void Display::clearLine(uint8_t lineNum) {
  ssd1306_setpos(0, lineNum);
  ssd1306_start_data();
  for (uint16_t i = 0; i < 128; i++) {
    ssd1306_data_byte(0x0);
  }
  ssd1306_stop();
}
