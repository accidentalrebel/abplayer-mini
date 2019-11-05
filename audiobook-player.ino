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

#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include <ssd1306xled.h>

#define V_NOMINAL 3.7
#define V_DROP_1 1.4567
#define V_DROP_2 0.8297
#define V_DROP_3 0.3947
#define V_DROP_4 0.1877
#define ALLOWANCE 30

#define IS_ATTINY_85 true

#if IS_ATTINY_85 == true
/// ATTINY85
#define RX PB4
#define TX PB1
SoftwareSerial Serial(RX, TX);

#define SSD1306_SCL PB2	
#define SSD1306_SDA	PB0

#else
/// Arduino
#define RX 10
#define TX 11

#endif

uint16_t playIndex = 0;
bool isSwitching = false;
int analogValue = 0;

class Mp3Notify;
SoftwareSerial secondarySerial(RX, TX);
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);

void log(char* log, bool canClear = false) {
	if ( canClear ) {
		SSD1306.ssd1306_fillscreen(0x00);
	}
	SSD1306.ssd1306_string_font6x8(log);
}

void logInt(uint16_t val, bool canClear = false) {
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%u", val);
	log(buffer, canClear);
}

class Input {
 public:
	static bool isAnyKeyPressed;

	static uint16_t getKeyPress(int analogValue) {
		if ( Input::detectKeyPress(analogValue, V_DROP_1)	) {
			return 1;
		}
		else if ( Input::detectKeyPress(analogValue, V_DROP_2)	) {
			return 2;
		}
		else if ( Input::detectKeyPress(analogValue, V_DROP_3)	) {
			return 3;
		}
		else if ( Input::detectKeyPress(analogValue, V_DROP_4)	) {
			return 4;
		}
		return 0;
	}
	
	static bool detectKeyPress(int readValue, float voltageDrop) {
		float change = voltageDrop / V_NOMINAL;
		float computed = 1023 * change;
		if ( readValue >= computed - ALLOWANCE && readValue <= computed + ALLOWANCE ) {
			return true;
		}
		return false;
	}
};
bool Input::isAnyKeyPressed = false;

class Player {
 public:
	static bool isPlaying;
	
	static void playNextTrack() {
		if ( !isSwitching ) {
			isSwitching = true;
			
			playIndex++;
			if ( playIndex > 3 ) {
				playIndex = 1;
			}
		
			//The delays and mp3.stop() helped fixed the COM 131 error.
			delay(30);
			mp3.stop();
			delay(30);
			mp3.playFolderTrack(1, playIndex);
			delay(300);

			log("Playing ", true);
			logInt(playIndex);

			isSwitching = false;
			isPlaying = true;
		}
	}

	static void resume() {
		if ( isPlaying ) {
			return;
		}

		mp3.start();
		isPlaying = true;
	}

	static void pause() {
		if ( !isPlaying ) {
			return;
		}

		mp3.pause();
		isPlaying = false;
	}
};
bool Player::isPlaying = false;

class Mp3Notify
{
public:
  static void OnError(uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
		SSD1306.ssd1306_setpos(3, 0);
    log("Error ", true);
    logInt(errorCode);

		digitalWrite(PB3, HIGH);
  }

  static void OnPlayFinished(uint16_t globalTrack)
  {
		SSD1306.ssd1306_setpos(3, 0);
    log("Finished ");
    logInt(globalTrack);
		log(".");

		Player::playNextTrack();
  }

  static void OnCardOnline(uint16_t code)
  {
		SSD1306.ssd1306_setpos(3, 0);
    log("Card online", true);
    //logInt(code);     
  }

  static void OnUsbOnline(uint16_t code)
  {
		SSD1306.ssd1306_setpos(3, 0);
    log("USB Disk online", true);
    //logInt(code);     
  }

  static void OnCardInserted(uint16_t code)
  {
		SSD1306.ssd1306_setpos(3, 0);
    log("Card inserted", true);
    //logInt(code); 
  }

  static void OnUsbInserted(uint16_t code)
  {
		SSD1306.ssd1306_setpos(3, 0);
    log("USB Disk inserted", true);
    //logInt(code); 
  }

  static void OnCardRemoved(uint16_t code)
  {
		SSD1306.ssd1306_setpos(3, 0);
    log("Card removed", true);
    //logInt(code);  
  }

  static void OnUsbRemoved(uint16_t code)
  {
		SSD1306.ssd1306_setpos(3, 0);
    log("USB Disk removed", true);
    //logInt(code);  
  }
};

void setup() {
	analogReference(DEFAULT);
	
  SSD1306.ssd1306_init();
	SSD1306.ssd1306_fillscreen(0x00);

	pinMode(A3, INPUT);
	pinMode(PB3, OUTPUT);

	Serial.begin(115200);

	digitalWrite(PB3, HIGH);
	delay(1000);
	mp3.begin();
	mp3.reset();
	digitalWrite(PB3, LOW);
	delay(500);

	uint16_t volume = mp3.getVolume();
	mp3.setVolume(24);
	delay(30);
  
	uint16_t count = mp3.getTotalTrackCount();

	Player::playNextTrack();
}

void loop() {
	if ( !isSwitching ) {
		mp3.loop();

		analogValue = analogRead(A3);

		uint16_t key = Input::getKeyPress(analogValue);
		if ( !Input::isAnyKeyPressed && key > 0 ) {
			SSD1306.ssd1306_setpos(3, 3);
			if ( key == 1 ) {
				SSD1306.ssd1306_string_font6x8("Button 1");
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
				SSD1306.ssd1306_string_font6x8("Button 3");
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
