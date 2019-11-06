#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

class Player {
 public:
  static uint16_t playIndex;	
  static bool isSwitching;
  static bool isPlaying;
	
  static void playNextTrack();
  static void playPrevTrack();
  static void playCurrentTrack();
  static void resume();
  static void pause();
};

#endif
