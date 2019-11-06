#include "Player.h"

bool Player::isPlaying = false;
bool Player::isSwitching = false;
uint16_t Player::playIndex = 0;

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

  Display::log("Playing ", true);
  Display::logInt(Player::playIndex);

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
