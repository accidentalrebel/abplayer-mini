#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include "AudioBookPlayer.h"

class Input {
 public:
  static bool isAnyKeyPressed;
  static uint16_t getKeyPress(int analogValue);
  static bool detectKeyPress(int readValue, float voltageDrop);
};

#endif
