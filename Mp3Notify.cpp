#include "Mp3Notify.h"

static void Mp3Notify::OnError(uint16_t errorCode)
{
  // see DfMp3_Error for code meaning
  SSD1306.ssd1306_setpos(3, 0);
  Display::log("Error ");
  Display::logInt(errorCode);
}

static void Mp3Notify::OnPlayFinished(uint16_t globalTrack)
{
  SSD1306.ssd1306_setpos(3, 0);
  Display::log("Finished ");
  Display::logInt(globalTrack);
  Display::log(".");

  Player::playNextTrack();
}

static void Mp3Notify::OnCardOnline(uint16_t code)
{
  SSD1306.ssd1306_setpos(3, 0);
  Display::log("Card online", true);
  //Display::logInt(code);     
}

static void Mp3Notify::OnUsbOnline(uint16_t code)
{
  SSD1306.ssd1306_setpos(3, 0);
  Display::log("USB Disk online", true);
  //Display::logInt(code);     
}

static void Mp3Notify::OnCardInserted(uint16_t code)
{
  SSD1306.ssd1306_setpos(3, 0);
  Display::log("Card inserted", true);
  //Display::logInt(code); 
}

static void Mp3Notify::OnUsbInserted(uint16_t code)
{
  SSD1306.ssd1306_setpos(3, 0);
  Display::log("USB Disk inserted", true);
  //Display::logInt(code); 
}

static void Mp3Notify::OnCardRemoved(uint16_t code)
{
  SSD1306.ssd1306_setpos(3, 0);
  Display::log("Card removed", true);
  //Display::logInt(code);  
}

static void Mp3Notify::OnUsbRemoved(uint16_t code)
{
  SSD1306.ssd1306_setpos(3, 0);
  Display::log("USB Disk removed", true);
  //Display::logInt(code);  
}

