#include "Mp3Notify.h"

static void Mp3Notify::OnError(uint16_t errorCode)
{
  // see DfMp3_Error for code meaning
  Display::clearLine(6);
  ssd1306_setpos(3, 7);
  Display::log("> Error ");
  Display::logInt(errorCode);
}

static void Mp3Notify::OnPlayFinished(uint16_t globalTrack)
{
  ssd1306_setpos(3, 7);
  Display::log("> Finished ");
  Display::logInt(globalTrack);

  Player::onPlayFinished();
}

static void Mp3Notify::OnCardOnline(uint16_t code)
{
  ssd1306_setpos(3, 7);
  Display::log("> Card online");
}

static void Mp3Notify::OnUsbOnline(uint16_t code)
{
  ssd1306_setpos(3, 7);
  Display::log("> USB Disk online");
}

static void Mp3Notify::OnCardInserted(uint16_t code)
{
  ssd1306_setpos(3, 7);
  Display::log("> Card inserted");
}

static void Mp3Notify::OnUsbInserted(uint16_t code)
{
  ssd1306_setpos(3, 7);
  Display::log("> USB Disk inserted");
}

static void Mp3Notify::OnCardRemoved(uint16_t code)
{
  ssd1306_setpos(3, 7);
  Display::log("> Card removed");
}

static void Mp3Notify::OnUsbRemoved(uint16_t code)
{
  ssd1306_setpos(3, 7);
  Display::log("> USB Disk removed");
}

