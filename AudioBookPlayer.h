#ifndef AUDIOBOOKPLAYER_H
#define AUDIOBOOKPLAYER_H

#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include <ssd1306xled.h>
#include "Input.h"
#include "Player.h"

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

#define SSD1306_SCL PB2	
#define SSD1306_SDA	PB0

#else
/// Arduino
#define RX 10
#define TX 11

#endif

#ifndef MP3NOTIFY_H
#define MP3NOTIFY_H
class Mp3Notify;
#endif

class AudioBookPlayer {
 public:
  static SoftwareSerial secondarySerial;
  static DFMiniMp3<SoftwareSerial, Mp3Notify> mp3;

  static void log(char* log, bool canClear = false);
  static void logInt(uint16_t val, bool canClear = false);
};

#endif
