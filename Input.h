#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include "AudioBookPlayer.h"

class Input {
 public:
  static uint16_t pressedButton;
  static uint16_t releasedButton;
  static bool isAnyButtonPressed;
  static void loop();
  static bool onButtonReleased(uint16_t buttonNumber);
  static uint16_t getButtonPress(int analogValue);
  static bool detectButtonPress(int readValue, float voltageDrop);
};

#endif
