#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <font6x8.h>
#include <ssd1306xled.h>
#include <ssd1306xledtx.h>

class Display {
  static char* convertInt(uint16_t val);
  static void setupMessage(bool canClear);
 public:
  static bool isTurnedOn;
  static void init();
  static void sleep();
  static void wake();
  static void log(char* log, bool canClear = false);
  static void logInt(uint16_t val, bool canClear = false);
  
  static void onUpdatedMode(char* mode);
  static void onUpdateMessage(char* message, bool canClear = false);
  static void onUpdateMessageNum(uint16_t num, bool canClear = false);
  static void onUpdateCurrentPlayed(uint16_t trackNum, uint16_t maxNum);
  static void onUpdatedVolume(uint16_t vol);
  
  static void clearLine(uint8_t lineNum);
};

#endif
