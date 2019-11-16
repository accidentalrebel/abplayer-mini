#include "System.h"

bool System::isSleeping = false;
bool System::canSleep = false;

void System::loop() {
  Input::loop();

  if ( !isSleeping ){ 
    AudioBookPlayer::mp3.loop();
    
    if ( Input::pressedButton == 2 && Input::pressedDuration >= 1000 ) {
      Display::sleep();
      canSleep = true;
    }
    else if ( canSleep && Input::releasedButton == 2 ) {
      canSleep = false;
      sleep();
    }
  }
}

void System::sleep() {
  if ( isSleeping ) {
    return;
  }
  isSleeping = true;
	
  ssd1306_setpos(3, 7);
  Display::log("> Sleep");

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
  Player::wake();
	
  ssd1306_setpos(3, 7);
  Display::log("> Awake");

  isSleeping = false;
}

/* ISR(PCINT0_vect) { } */ 
