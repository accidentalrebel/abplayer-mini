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

	uint16_t volume = AudioBookPlayer::mp3.getVolume();
	AudioBookPlayer::mp3.setVolume(24);
	delay(30);
  
	uint16_t count = AudioBookPlayer::mp3.getTotalTrackCount();

	Player::playNextTrack();
}

void loop() {
	if ( !Player::isSwitching ) {
		AudioBookPlayer::mp3.loop();
		Input::loop();

		SSD1306.ssd1306_setpos(3, 3);
		if ( Input::pressedButton > 0 && Input::pressedDuration >= 2000 ) {
			if ( Display::isTurnedOn ) {
				Display::sleep();
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
					SSD1306.ssd1306_string_font6x8("Pausing");
				}
				else {
					Player::resume();
					SSD1306.ssd1306_string_font6x8("Resuming");
				}
			}
			else if ( Input::releasedButton == 3 ) {
				Player::playNextTrack();
			}
			else if ( Input::releasedButton == 4 ) {
				if ( !Display::isTurnedOn ) {
					Display::wake();
				}
				SSD1306.ssd1306_string_font6x8("Button 4");
			}
		}
	}
}
