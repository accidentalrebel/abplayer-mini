#include "AudioBookPlayer.h"

bool needsReset = false;


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

void loop() {
	if ( Player::isSwitching ) {
		return;
	}
	
  System::loop();

	SSD1306.ssd1306_setpos(2, 2);
	Display::logInt(Input::pressedButton, false);

	SSD1306.ssd1306_setpos(3, 3);
	
	if ( !System::isSleeping && Input::pressedButton > 0 ) {
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
				Display::sleep();
				System::canSleep = true;
				needsReset = false;
			}
		}
	}
	else if ( Input::releasedButton > 0 ) {
		if ( System::isSleeping ) {
			Display::log("Waking Player");
			Player::wake();
			delay(5000);
	
			Display::log("Awoken Player");
			delay(1000);
				
			System::isSleeping = false;
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
				if ( System::canSleep ) {
					System::sleep();
					System::canSleep = false;
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
