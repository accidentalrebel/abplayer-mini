#include "Player.h"

bool Player::isPlaying = false;
bool Player::isSwitching = false;
uint16_t Player::playIndex = 0;

static void Player::playNextTrack() {
  if ( isSwitching ) {
    return;
  }
  playIndex++;
  if ( playIndex > 4 ) {
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
    playIndex = 4u;
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

static void Player::sleep() {
  if ( isPlaying ) {
    pause();
  }
  AudioBookPlayer::mp3.sleep();
}

static void Player::wake() {
  AudioBookPlayer::mp3.setPlaybackSource(DfMp3_PlaySource_Sd);
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

static void Player::setVolume(uint8_t val) {
  if ( val > 30 ) {
    val = 30;
  }
  AudioBookPlayer::mp3.setVolume(val);
}

static uint8_t Player::getVolume() {
  return AudioBookPlayer::mp3.getVolume();
}

static void Player::decreaseVolume() {
  uint8_t currentVolume = getVolume();
  setVolume(currentVolume - 5);
}

static void Player::increaseVolume() {
  uint8_t currentVolume = getVolume();
  setVolume(currentVolume + 5);
}




