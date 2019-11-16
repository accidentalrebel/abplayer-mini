#include "Player.h"

#define SEEK_JUMP_COUNT 20;

bool Player::isPlaying = false;
bool Player::isSwitching = false;
bool Player::isSeekMode = false;
bool Player::onPlayFinishedTrigger = false;

uint16_t Player::playIndex = 0;

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

  playNextTrack(false);
  onPlayFinishedTrigger = false;
}

static void Player::playNextTrack(bool canSeek = true) {
  if ( isSwitching ) {
    return;
  }
  uint8_t jumpAmount = 1;
  if ( canSeek && isSeekMode ) {
    jumpAmount = SEEK_JUMP_COUNT;
  }
  if ( playIndex + jumpAmount > AudioBookPlayer::mp3.getTotalTrackCount() ) {
    playIndex = 1;
  }
  else {
    playIndex += jumpAmount;
  }

  resetMode();
  playCurrentTrack();
}

static void Player::playPrevTrack(bool canSeek = true) {
  if ( isSwitching ) {
    return;
  }

  uint8_t jumpAmount = 1;
  if ( canSeek && isSeekMode ) {
    jumpAmount = SEEK_JUMP_COUNT;
  }

  if ( playIndex - jumpAmount <= 0 || playIndex < jumpAmount ) {
    playIndex = AudioBookPlayer::mp3.getTotalTrackCount();
  }
  else {
    playIndex -= jumpAmount;
  }

  resetMode();
  playCurrentTrack();
}

static void Player::playCurrentTrack() {
  isSwitching = true;

  AudioBookPlayer::mp3.playGlobalTrack(Player::playIndex);
  Display::onUpdateCurrentPlayed(Player::playIndex);

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

static void Player::toggleMode() {
  if( isSeekMode ) {
    resetMode();
  }
  else {
    isSeekMode = true;
    Display::onUpdatedMode("Seek");
  }
}

static void Player::resetMode() {
  isSeekMode = false;
  Display::onUpdatedMode("Normal");
}




