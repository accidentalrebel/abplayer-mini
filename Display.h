#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <ssd1306xled.h>

class Display {
 public:
  static void log(char* log, bool canClear = false);
  static void logInt(uint16_t val, bool canClear = false);
};

#endif
