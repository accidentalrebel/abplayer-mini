#ifndef SYSTEM_H
#define SYSTEM_H

#include "Display.h"
#include "Player.h"
#include "Input.h"

class System {
  static bool canSleep;
public:
  static bool isSleeping;
  static void sleep();
  static void loop();
};

#endif
