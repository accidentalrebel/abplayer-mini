#include "System.h"

bool System::canSleep = false;
bool System::isSleeping = false;

void System::loop() {
  Input::loop();

  if ( !isSleeping ) {
    AudioBookPlayer::mp3.loop();
    
    if ( Input::pressedButton == 2 && Input::pressedDuration >= 1000 ) {
      Display::sleep();
      canSleep = true;
    }
    else if ( Input::releasedButton == 2 && canSleep ) {
      sleep();
      canSleep = false;
    }
  }
  else {
    Display::log("Waking Player");
    Player::wake();
    delay(5000);
	
    Display::log("Awoken Player");
    delay(1000);
				
    isSleeping = false;
  }
}

void System::sleep() {
  isSleeping = true;
	
  SSD1306.ssd1306_setpos(1, 1);
  Display::log("Sleep");

  Display::sleep();
  Player::sleep();
	
  GIMSK |= _BV(PCIE); // Enabel Pin change interrupt
  PCMSK |= _BV(PCINT3); // USE PB3 as interrupt
  ADCSRA &= ~_BV(ADEN); // ADC off
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  sleep_enable(); // Sets the sleep enable
  sei(); // Enable interrupts
  sleep_cpu();

  cli(); // Disable interrupts
  PCMSK &= ~_BV(PCINT3); // Turn off PB3 as interrupt
  ADCSRA |= _BV(ADEN); // ADC on

  sei(); // Enable interrupts

  Display::wake();
	
  SSD1306.ssd1306_setpos(1, 1);
  Display::log("Awake");
}

/* ISR(PCINT0_vect) { } */ 