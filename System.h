#ifndef SYSTEM_H
#define SYSTEM_H

#include "Display.h"
#include "Player.h"
#include "Input.h"

class System {
 public:
  static bool canSleep;
  static bool isSleeping;
  static void sleep();
  static void loop();
};

#endif
