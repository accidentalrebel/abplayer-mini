#include "Player.h"

bool Player::isPlaying = false;
bool Player::isSwitching = false;
uint8_t Player::playIndex = 0;
bool Player::onPlayFinishedTrigger = false;

/*
 * According to the documentation OnPlayFinished is called twice.
 * So we use onPlayFinishedTrigger to make sure we only play the
 * next track on the second time onPlayFinished is called.
 */
static void Player::onPlayFinished() {
  if ( !onPlayFinishedTrigger ) {
    onPlayFinishedTrigger = true;
    return;
  }

  playNextTrack();
  onPlayFinishedTrigger = false;
}

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
    playIndex = 4;
  }

  playCurrentTrack();
}

static void Player::playCurrentTrack() {
  isSwitching = true;

  AudioBookPlayer::mp3.playFolderTrack(1, Player::playIndex);

  Display::onUpdateCurrentPlayed(1, Player::playIndex);

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
  delay(1000);

  playCurrentTrack();
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
  Display::onUpdatedVolume(val);
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




