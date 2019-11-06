#include "Mp3Notify.h"

static void Mp3Notify::OnError(uint16_t errorCode)
{
  // see DfMp3_Error for code meaning
  SSD1306.ssd1306_setpos(3, 0);
  AudioBookPlayer::log("Error ", true);
  AudioBookPlayer::logInt(errorCode);

  digitalWrite(PB3, HIGH);
}

static void Mp3Notify::OnPlayFinished(uint16_t globalTrack)
{
  SSD1306.ssd1306_setpos(3, 0);
  AudioBookPlayer::log("Finished ");
  AudioBookPlayer::logInt(globalTrack);
  AudioBookPlayer::log(".");

  Player::playNextTrack();
}

static void Mp3Notify::OnCardOnline(uint16_t code)
{
  SSD1306.ssd1306_setpos(3, 0);
  AudioBookPlayer::log("Card online", true);
  //AudioBookPlayer::logInt(code);     
}

static void Mp3Notify::OnUsbOnline(uint16_t code)
{
  SSD1306.ssd1306_setpos(3, 0);
  AudioBookPlayer::log("USB Disk online", true);
  //AudioBookPlayer::logInt(code);     
}

static void Mp3Notify::OnCardInserted(uint16_t code)
{
  SSD1306.ssd1306_setpos(3, 0);
  AudioBookPlayer::log("Card inserted", true);
  //AudioBookPlayer::logInt(code); 
}

static void Mp3Notify::OnUsbInserted(uint16_t code)
{
  SSD1306.ssd1306_setpos(3, 0);
  AudioBookPlayer::log("USB Disk inserted", true);
  //AudioBookPlayer::logInt(code); 
}

static void Mp3Notify::OnCardRemoved(uint16_t code)
{
  SSD1306.ssd1306_setpos(3, 0);
  AudioBookPlayer::log("Card removed", true);
  //AudioBookPlayer::logInt(code);  
}

static void Mp3Notify::OnUsbRemoved(uint16_t code)
{
  SSD1306.ssd1306_setpos(3, 0);
  AudioBookPlayer::log("USB Disk removed", true);
  //AudioBookPlayer::logInt(code);  
}

