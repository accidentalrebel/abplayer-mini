#include "AudioBookPlayer.h"

bool needsReset = false;

SoftwareSerial AudioBookPlayer::secondarySerial = SoftwareSerial(RX, TX);
DFMiniMp3<SoftwareSerial, Mp3Notify> AudioBookPlayer::mp3 = DFMiniMp3<SoftwareSerial, Mp3Notify>(AudioBookPlayer::secondarySerial);

void setup() {
	Display::init();

	AudioBookPlayer::mp3.begin();

	delay(1000);
	
	Player::setup();
	Player::setVolume(15);

	analogReference(DEFAULT);
	pinMode(A3, INPUT);
}

void loop() {
	if ( Player::isSwitching ) {
		return;
	}
	
  System::loop();

	if ( System::isSleeping ) {
		return;
	}

	/* ssd1306_setpos(3, 7); */
	/* Display::logInt(Input::pressedButton, false); */

	ssd1306_setpos(3, 7);
	
	if ( Input::pressedButton > 0 && !needsReset && Input::pressedDuration >= 1000) {
		if ( Input::pressedButton ==  1 ) {
			Player::decreaseVolume();
		}
		else if ( Input::pressedButton == 3 ) {
			Player::increaseVolume();
		}
		else if ( Input::pressedButton == 4 && Display::isTurnedOn ) {
			Display::sleep();
		}
		needsReset = true;
	}
	else if ( Input::releasedButton > 0 ) {
		if ( needsReset ) {
			needsReset = false;
			return;
		}
		if ( Input::pressedDuration >= 1000 ) {
			return;
		}
		if ( Input::releasedButton == 1 ) {
			Player::playPrevTrack();
		}
		else if ( Input::releasedButton == 2 ) {
			if ( Player::isPlaying ) {
				Player::pause();
				Display::onUpdateMessage("> Pausing", true);
			}
			else {
				Player::resume();
				Display::onUpdateMessage("> Resuming", true);
			}
		}
		else if ( Input::releasedButton == 3 ) {
			Player::playNextTrack();
		}
		else if ( Input::releasedButton == 4 ) {
			if ( !Display::isTurnedOn ) {
				Display::wake();
			}
			else {
				Player::toggleMode();
			}
		}
	}
}
