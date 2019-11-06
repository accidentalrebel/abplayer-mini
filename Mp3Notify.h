#ifndef MP3NOTIFY_H
#define MP3NOTIFY_H

#include <stdint.h>
#include <ssd1306xled.h>
#include "AudioBookPlayer.h"

class Mp3Notify
{
 public:
  static void OnError(uint16_t errorCode);
  static void OnPlayFinished(uint16_t globalTrack);
  static void OnCardOnline(uint16_t code);
  static void OnUsbOnline(uint16_t code);
  static void OnCardInserted(uint16_t code);
  static void OnUsbInserted(uint16_t code);
  static void OnCardRemoved(uint16_t code);
  static void OnUsbRemoved(uint16_t code);
};

#endif
