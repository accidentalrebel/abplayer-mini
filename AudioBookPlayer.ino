#include "AudioBookPlayer.h"

SoftwareSerial AudioBookPlayer::secondarySerial = SoftwareSerial(RX, TX);
DFMiniMp3<SoftwareSerial, Mp3Notify> AudioBookPlayer::mp3 = DFMiniMp3<SoftwareSerial, Mp3Notify>(AudioBookPlayer::secondarySerial);

void setup() {
	analogReference(DEFAULT);
	
  SSD1306.ssd1306_init();
	SSD1306.ssd1306_fillscreen(0x00);

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

		int analogValue = analogRead(A3);

		uint16_t key = Input::getKeyPress(analogValue);
		if ( !Input::isAnyKeyPressed && key > 0 ) {
			SSD1306.ssd1306_setpos(3, 3);
			if ( key == 1 ) {
				Player::playPrevTrack();
			}
			else if ( key == 2 ) {
				if ( Player::isPlaying ) {
					Player::pause();
					SSD1306.ssd1306_string_font6x8("Pausing");
				}
				else {
					Player::resume();
					SSD1306.ssd1306_string_font6x8("Resuming");
				}
			}
			else if ( key == 3 ) {
				Player::playNextTrack();
			}
			else if ( key == 4 ) {
				SSD1306.ssd1306_string_font6x8("Button 4");
			}
			Input::isAnyKeyPressed = true;
		}
		else if ( Input::isAnyKeyPressed && key <= 0 ) {
			Input::isAnyKeyPressed = false;
		}
	}
}
