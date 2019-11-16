#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <ssd1306xled.h>
#include <ssd1306xledtx.h>
#include "AudioBookPlayer.h"
#include "Display.h"

class Player {
 public:
  static uint16_t playIndex;
  static bool isSwitching;
  static bool isPlaying;
  static bool onPlayFinishedTrigger;
  static bool isSeekMode;

  static void onPlayFinished();
  static void playNextTrack(bool canSeek = true);
  static void playPrevTrack(bool canSeek = true);
  static void playCurrentTrack();
  static void sleep();
  static void wake();
  static void resume();
  static void pause();
  static void setVolume(uint8_t vol);
  static uint8_t getVolume();
  static void decreaseVolume();
  static void increaseVolume();
  static void toggleMode();
  static void resetMode();
};

#endif
