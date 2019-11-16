#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <Arduino.h>
#include "AudioBookPlayer.h"

class Input {
  static unsigned long timePressed;
 public:
  static unsigned long pressedDuration;
  static uint16_t pressedButton;
  static uint16_t releasedButton;
  static bool isAnyButtonPressed;
  static void loop();
  static bool onButtonReleased(uint16_t buttonNumber);
  static uint16_t getButtonPress();
  static bool detectButtonPress(int buttonToCheck);
};

#endif
