#include "AudioBookPlayer.h"

bool needsReset = false;

SoftwareSerial AudioBookPlayer::secondarySerial = SoftwareSerial(RX, TX);
DFMiniMp3<SoftwareSerial, Mp3Notify> AudioBookPlayer::mp3 = DFMiniMp3<SoftwareSerial, Mp3Notify>(AudioBookPlayer::secondarySerial);

void setup() {
	analogReference(DEFAULT);

	Display::init();

	pinMode(A3, INPUT);
	pinMode(PB3, OUTPUT);

	digitalWrite(PB3, HIGH);
	delay(1000);
	AudioBookPlayer::mp3.begin();
	AudioBookPlayer::mp3.reset();
	digitalWrite(PB3, LOW);
	delay(500);
	Player::setVolume(30);
	delay(30);
  
	uint16_t count = AudioBookPlayer::mp3.getTotalTrackCount();

	Player::playNextTrack();
}

void loop() {
	if ( !Player::isSwitching ) {
		AudioBookPlayer::mp3.loop();
		Input::loop();

		SSD1306.ssd1306_setpos(2, 2);
		Display::logInt(Input::pressedButton, false);

		SSD1306.ssd1306_setpos(3, 3);
		if ( Input::pressedButton > 0 ) {
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
			}
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
				if ( Player::isPlaying ) {
					Player::pause();
					Display::log("Pausing");
				}
				else {
					Player::resume();
					Display::log("Resuming");
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
