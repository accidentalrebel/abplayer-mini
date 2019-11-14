#include "AudioBookPlayer.h"

bool needsReset = false;
bool canSleep = false;
bool isSleeping = false;

SoftwareSerial AudioBookPlayer::secondarySerial = SoftwareSerial(RX, TX);
DFMiniMp3<SoftwareSerial, Mp3Notify> AudioBookPlayer::mp3 = DFMiniMp3<SoftwareSerial, Mp3Notify>(AudioBookPlayer::secondarySerial);

void setup() {
	Display::init();

	AudioBookPlayer::mp3.begin();
	Player::setVolume(15);

	delay(1000);

	Player::playNextTrack();

	analogReference(DEFAULT);
	pinMode(A3, INPUT);
}

void sleep() {
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

void loop() {
	if ( !Player::isSwitching ) {

		if ( !isSleeping ) {
			AudioBookPlayer::mp3.loop();
		}

		Input::loop();
		SSD1306.ssd1306_setpos(2, 2);
		Display::logInt(Input::pressedButton, false);

		/* SSD1306.ssd1306_setpos(5, 5); */
		/* float button = ceil(((analogRead(A3)*5)+512)/1024); */
		/* Display::logInt(button); */
		/* SSD1306.ssd1306_setpos(6, 6); */
		/* Display::logInt(analogRead(A3)); */
		/* delay(500); */
		/* return; */

		SSD1306.ssd1306_setpos(3, 3);
		if ( !isSleeping && Input::pressedButton > 0 ) {
			if ( !needsReset && Input::pressedDuration >= 1000 ) {
				if ( Input::pressedButton ==  1 ) {
					Player::decreaseVolume();
					Display::log("decreased volume to ");
					Display::logInt(Player::getVolume());
				}
				else if ( Input::pressedButton == 3 ) {
					Player::increaseVolume();
					Display::log("Increased volume to ");
					Display::logInt(Player::getVolume());
				}
				else if ( Input::pressedButton == 4 && Display::isTurnedOn ) {
					Display::sleep();
				}
				needsReset = true;
				
				if ( Input::pressedButton == 2 ) {
					canSleep = true;
					needsReset = false;
				}
			}
		}
		else if ( Input::releasedButton > 0 ) {
			if ( isSleeping ) {
				Display::log("Waking Player");
				Player::wake();
				delay(5000);
	
				Display::log("Awoken Player");
				delay(1000);
				
				isSleeping = false;
			}
			else {
				if ( needsReset ) {
					needsReset = false;
					return;
				}
				if ( Input::releasedButton == 1 ) {
					Player::playPrevTrack();
				}
				else if ( Input::releasedButton == 2 ) {
					if ( canSleep ) {
						sleep();
						canSleep = false;
					}
					else {
						if ( Player::isPlaying ) {
							Player::pause();
							Display::log("Pausing");
						}
						else {
							Player::resume();
							Display::log("Resuming");
						}
					}
				}
				else if ( Input::releasedButton == 3 ) {
					Player::playNextTrack();
				}
				else if ( Input::releasedButton == 4 ) {
					if ( !Display::isTurnedOn ) {
						Display::wake();
					}
					Display::log("Button 4");
				}
			}
		}
	}
}
