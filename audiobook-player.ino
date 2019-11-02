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

/// ATTINY85
/* #define RX PB0 */
/* #define TX PB2 */
/* SoftwareSerial Serial(RX, TX); */

/// Arduino
#define RX 10
#define TX 11

uint8_t playIndex = 0;
bool isSwitching = false;

class Mp3Notify;

class Player {
 public:
	static DFMiniMp3<SoftwareSerial, Mp3Notify> mp3;

	static void setup() {
		Serial.begin(115200);

		Serial.println("initializing...");

		delay(5000); // It was suggested to have a 5 second delay before starting
		mp3.begin();
		delay(30);

		uint16_t volume = mp3.getVolume();
		Serial.print("volume ");
		Serial.println(volume);
		mp3.setVolume(24);
		delay(30);
  
		uint16_t count = mp3.getTotalTrackCount();
		Serial.print("files ");
		Serial.println(count);

		Serial.println("starting...");

		Player::playNextTrack();
	}

	static void loop() {
		mp3.loop();
	}

	static void playNextTrack() {
		if ( !isSwitching ) {
			isSwitching = true;
			
			playIndex++;
			if ( playIndex > 3 ) {
				playIndex = 1;
			}
		
			Serial.print("Playing ");
			Serial.println(playIndex);
			Serial.println("...");

			//The delays and mp3.stop() helped fixed the COM 131 error.
			delay(30);
			mp3.stop();
			delay(30);
			mp3.playFolderTrack(1, playIndex);
			delay(300);

			Serial.print("Now playing ");
			Serial.println(playIndex);

			isSwitching = false;
		}
	}
};

class Mp3Notify
{
public:
  static void OnError(uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }

  static void OnPlayFinished(uint16_t globalTrack)
  {
    Serial.println();
    Serial.print("OnPlayFinished for #");
    Serial.println(globalTrack);

		Player::playNextTrack();
  }

  static void OnCardOnline(uint16_t code)
  {
    Serial.println();
    Serial.print("Card online ");
    Serial.println(code);     
  }

  static void OnUsbOnline(uint16_t code)
  {
    Serial.println();
    Serial.print("USB Disk online ");
    Serial.println(code);     
  }

  static void OnCardInserted(uint16_t code)
  {
    Serial.println();
    Serial.print("Card inserted ");
    Serial.println(code); 
  }

  static void OnUsbInserted(uint16_t code)
  {
    Serial.println();
    Serial.print("USB Disk inserted ");
    Serial.println(code); 
  }

  static void OnCardRemoved(uint16_t code)
  {
    Serial.println();
    Serial.print("Card removed ");
    Serial.println(code);  
  }

  static void OnUsbRemoved(uint16_t code)
  {
    Serial.println();
    Serial.print("USB Disk removed ");
    Serial.println(code);  
  }
};

SoftwareSerial secondarySerial(RX, TX); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> Player::mp3(secondarySerial);

void setup() { Player::setup(); }
void loop() { Player::loop(); }
