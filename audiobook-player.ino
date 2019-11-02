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

// implement a notification class,
// its member methods will get called 
//

bool isPlaying = false;
uint8_t playIndex = 0;

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
    Serial.print("Play finished for #");
    Serial.println(globalTrack);

		isPlaying = false;
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

// instance a DFMiniMp3 object, 
// defined with the above notification class and the hardware serial class
//
//DFMiniMp3<HardwareSerial, Mp3Notify> mp3(Serial1);

// Some arduino boards only have one hardware serial port, so a software serial port is needed instead.
// comment out the above definition and uncomment these lines
SoftwareSerial secondarySerial(RX, TX); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);

void setup() 
{
  Serial.begin(115200);

  Serial.println("initializing...");
  
  mp3.begin();

  uint16_t volume = mp3.getVolume();
  Serial.print("volume ");
  Serial.println(volume);
  mp3.setVolume(24);
  
  uint16_t count = mp3.getTotalTrackCount();
  Serial.print("files ");
  Serial.println(count);

	//mp3.playMp3FolderTrack(1);
  
  Serial.println("starting...");
}

void waitMilliseconds(uint16_t msWait)
{
  uint32_t start = millis();
  
  while ((millis() - start) < msWait)
  {
    // calling mp3.loop() periodically allows for notifications 
    // to be handled without interrupts
    mp3.loop(); 
    delay(1);
  }
}

void loop() 
{
	/* waitMilliseconds(5000); */
  /* mp3.nextTrack(); */

	if ( !isPlaying ) {
		playIndex ++;
		if ( playIndex > 3 ) {
			playIndex = 1;
		}

		mp3.playFolderTrack(1, playIndex);
		isPlaying = true;
	}
	
	mp3.loop();
	
	/* Serial.println("track 1");  */
  /* mp3.playFolderTrack(1, 1);  // sd:/01/001.mp3 */
  
  /* waitMilliseconds(5000); */
  
  /* Serial.println("track 2");  */
  /* mp3.playFolderTrack(1, 2); // sd:/01/002.mp3 */
  
  /* waitMilliseconds(5000); */
  
  /* Serial.println("track 3"); */
  /* mp3.playFolderTrack(1, 3); // sd:/01/003.mp3 */
  
  /* waitMilliseconds(5000); */
}
