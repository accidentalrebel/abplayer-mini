// this example will play a track and then 
// every five seconds play another track
//
// it expects the sd card to contain these three mp3 files
// but doesn't care whats in them
//
// sd:/mp3/0001.mp3
// sd:/mp3/0002.mp3
// sd:/mp3/0003.mp3

/* DfMp3_Error_Busy = 1 - (see chip documentation) Usually the media was not found. */
/* DfMp3_Error_Sleeping = 2 - (see chip documentation) The chip is in sleep mode. */
/* DfMp3_Error_SerialWrongStack = 3 - (see chip documentation) */
/* DfMp3_Error_CheckSumNotMatch = 4 - (see chip documentation) Communications error on the hardware level. Check wiring and GND connections. */
/* DfMp3_Error_FileIndexOut = 5 - (see chip documentation) File index out of bounds. */
/* DfMp3_Error_FileMismatch = 6 - (see chip documentation) Can not find file. */
/* DfMp3_Error_Advertise = 7 - (see chip documentation) In advertisement. */
/* DfMp3_Error_RxTimeout = 129 - An expected response from the device timed out while waiting. Check wiring. */
/* DfMp3_Error_PacketSize = 130 - The packet received from the device is the incorrect size. */
/* DfMp3_Error_PacketHeader = 131 - The packet received from the device had an incorrect header. */
/* DfMp3_Error_PacketChecksum = 132 - The packet received from the device had an incorrect checksum. */
/* DfMp3_Error_General = 255 - Inconclusive problem happened. */

#include "AudioBookPlayer.h"

SoftwareSerial AudioBookPlayer::secondarySerial = SoftwareSerial(RX, TX);
DFMiniMp3<SoftwareSerial, Mp3Notify> AudioBookPlayer::mp3 = DFMiniMp3<SoftwareSerial, Mp3Notify>(AudioBookPlayer::secondarySerial);

void AudioBookPlayer::log(char* log, bool canClear = false) {
	if ( canClear ) {
		SSD1306.ssd1306_fillscreen(0x00);
	}
	SSD1306.ssd1306_string_font6x8(log);
}

void AudioBookPlayer::logInt(uint16_t val, bool canClear = false) {
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%u", val);
	log(buffer, canClear);
}

static void Player::playNextTrack() {
	if ( isSwitching ) {
		return;
	}
	playIndex++;
	if ( playIndex > 3 ) {
		playIndex = 1;
	}

	playCurrentTrack();
}

static void Player::playPrevTrack() {
	if ( isSwitching ) {
		return;
	}
	playIndex--;
	if ( playIndex < 1 ) {
		playIndex = 3;
	}

	playCurrentTrack();
}

static void Player::playCurrentTrack() {
	isSwitching = true;

	//The delays and AudioBookPlayer::mp3.stop() helped fixed the COM 131 error.
	delay(30);
	AudioBookPlayer::mp3.stop();
	delay(30);
	AudioBookPlayer::mp3.playFolderTrack(1, Player::playIndex);
	delay(300);

	AudioBookPlayer::log("Playing ", true);
	AudioBookPlayer::logInt(Player::playIndex);

	isPlaying = true;
	isSwitching = false;
}

static void Player::resume() {
	if ( isPlaying ) {
		return;
	}

	AudioBookPlayer::mp3.start();
	isPlaying = true;
}

static void Player::pause() {
	if ( !isPlaying ) {
		return;
	}

	AudioBookPlayer::mp3.pause();
	isPlaying = false;
}

/* bool Player::isPlaying = false; */
/* bool Player::isSwitching = false; */
/* uint16_t Player::playIndex = 0; */

class Mp3Notify
{
 public:
  static void OnError(uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
		SSD1306.ssd1306_setpos(3, 0);
    AudioBookPlayer::log("Error ", true);
    AudioBookPlayer::logInt(errorCode);

		digitalWrite(PB3, HIGH);
  }

  static void OnPlayFinished(uint16_t globalTrack)
  {
		SSD1306.ssd1306_setpos(3, 0);
    AudioBookPlayer::log("Finished ");
    AudioBookPlayer::logInt(globalTrack);
		AudioBookPlayer::log(".");

		Player::playNextTrack();
  }

  static void OnCardOnline(uint16_t code)
  {
		SSD1306.ssd1306_setpos(3, 0);
    AudioBookPlayer::log("Card online", true);
    //AudioBookPlayer::logInt(code);     
  }

  static void OnUsbOnline(uint16_t code)
  {
		SSD1306.ssd1306_setpos(3, 0);
    AudioBookPlayer::log("USB Disk online", true);
    //AudioBookPlayer::logInt(code);     
  }

  static void OnCardInserted(uint16_t code)
  {
		SSD1306.ssd1306_setpos(3, 0);
    AudioBookPlayer::log("Card inserted", true);
    //AudioBookPlayer::logInt(code); 
  }

  static void OnUsbInserted(uint16_t code)
  {
		SSD1306.ssd1306_setpos(3, 0);
    AudioBookPlayer::log("USB Disk inserted", true);
    //AudioBookPlayer::logInt(code); 
  }

  static void OnCardRemoved(uint16_t code)
  {
		SSD1306.ssd1306_setpos(3, 0);
    AudioBookPlayer::log("Card removed", true);
    //AudioBookPlayer::logInt(code);  
  }

  static void OnUsbRemoved(uint16_t code)
  {
		SSD1306.ssd1306_setpos(3, 0);
    AudioBookPlayer::log("USB Disk removed", true);
    //AudioBookPlayer::logInt(code);  
  }
};

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
