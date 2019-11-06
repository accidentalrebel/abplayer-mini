#include "Input.h"

bool Input::isAnyKeyPressed = false;
static uint16_t Input::getKeyPress(int analogValue) {
  if ( Input::detectKeyPress(analogValue, V_DROP_1)	) {
    return 1;
  }
  else if ( Input::detectKeyPress(analogValue, V_DROP_2)	) {
    return 2;
  }
  else if ( Input::detectKeyPress(analogValue, V_DROP_3)	) {
    return 3;
  }
  else if ( Input::detectKeyPress(analogValue, V_DROP_4)	) {
    return 4;
  }
  return 0;
}
	
static bool Input::detectKeyPress(int readValue, float voltageDrop) {
  float change = voltageDrop / V_NOMINAL;
  float computed = 1023 * change;
  if ( readValue >= computed - ALLOWANCE && readValue <= computed + ALLOWANCE ) {
    return true;
  }
  return false;
}
