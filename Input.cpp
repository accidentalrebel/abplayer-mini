#include "Input.h"

bool Input::isAnyButtonPressed = false;
uint16_t Input::pressedButton = 0;
uint16_t Input::releasedButton = 0;
unsigned long Input::timePressed = 0;
unsigned long Input::pressedDuration = 0;

void Input::loop() {
  uint16_t button = Input::getButtonPress();
  if ( button > 0 ) {
    pressedButton = button;

    if ( timePressed == 0 ) {
      timePressed = millis();
      pressedDuration = 0;
    }
    else {
      pressedDuration = millis() - timePressed;
    }
  }
  else {
    releasedButton = pressedButton;
    pressedButton = 0;
    timePressed = 0;
  }
}

uint16_t Input::getButtonPress() {
  if ( Input::detectButtonPress(1) ) {
    return 1;
  }
  else if ( Input::detectButtonPress(2)	) {
    return 2;
  }
  else if ( Input::detectButtonPress(3)	) {
    return 3;
  }
  else if ( Input::detectButtonPress(4)	) {
    return 4;
  }
  return 0;
}
	
bool Input::detectButtonPress(int buttonToCheck) {
  int pressed = ceil(((analogRead(A3)*5)+512)/1024) + 1;
  if ( pressed == buttonToCheck ) {
    return true;
  }
  return false;
}
