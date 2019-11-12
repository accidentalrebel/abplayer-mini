#ifndef AUDIOBOOKPLAYER_H
#define AUDIOBOOKPLAYER_H

#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include <ssd1306xled.h>
#include "Input.h"
#include "Player.h"
#include "Mp3Notify.h"

#define V_NOMINAL 3.7
#define V_DROP_1 1.589
#define V_DROP_2 0.838
#define V_DROP_3 0.383
#define V_DROP_4 0.183
#define ALLOWANCE 40

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

class Mp3Notify;

class AudioBookPlayer {
 public:
  static SoftwareSerial secondarySerial;
  static DFMiniMp3<SoftwareSerial, Mp3Notify> mp3;
};

#endif
