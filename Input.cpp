#include "Input.h"

bool Input::isAnyButtonPressed = false;
uint16_t Input::pressedButton = 0;
uint16_t Input::releasedButton = 0;
unsigned long Input::timePressed = 0;
unsigned long Input::pressedDuration = 0;

void Input::loop() {
  int analogValue = analogRead(A3);
  uint16_t button = Input::getButtonPress(analogValue);
  if ( button > 0 ) {
    pressedButton = button;

    if ( timePressed == 0 ) {
      timePressed = millis();
      pressedDuration = 0;
    }
  }
  else {
    releasedButton = pressedButton;
    pressedButton = 0;

    SSD1306.ssd1306_setpos(4, 4);
    pressedDuration = millis() - timePressed;
    timePressed = 0;
  }
}

uint16_t Input::getButtonPress(int analogValue) {
  if ( Input::detectButtonPress(analogValue, V_DROP_1)	) {
    return 1;
  }
  else if ( Input::detectButtonPress(analogValue, V_DROP_2)	) {
    return 2;
  }
  else if ( Input::detectButtonPress(analogValue, V_DROP_3)	) {
    return 3;
  }
  else if ( Input::detectButtonPress(analogValue, V_DROP_4)	) {
    return 4;
  }
  return 0;
}
	
bool Input::detectButtonPress(int readValue, float voltageDrop) {
  float change = voltageDrop / V_NOMINAL;
  float computed = 1023 * change;
  if ( readValue > 20 && readValue >= computed - ALLOWANCE && readValue <= computed + ALLOWANCE ) {
    return true;
  }
  return false;
}
