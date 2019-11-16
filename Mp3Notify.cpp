#include "Mp3Notify.h"

static void Mp3Notify::OnError(uint16_t errorCode)
{
  // see DfMp3_Error for code meaning
  Display::onUpdateMessage("> Error ", true);
  Display::onUpdateMessageNum(errorCode);
}

static void Mp3Notify::OnPlayFinished(uint16_t globalTrack)
{
  Display::onUpdateMessage("> Finished ", true);
  Display::onUpdateMessageNum(globalTrack);

  Player::onPlayFinished();
}

static void Mp3Notify::OnCardOnline(uint16_t code)
{
  ssd1306_setpos(3, 7);
  Display::onUpdateMessage("> Card online");
}

static void Mp3Notify::OnUsbOnline(uint16_t code)
{
  ssd1306_setpos(3, 7);
  Display::onUpdateMessage("> USB Disk online");
}

static void Mp3Notify::OnCardInserted(uint16_t code)
{
  ssd1306_setpos(3, 7);
  Display::onUpdateMessage("> Card inserted");
}

static void Mp3Notify::OnUsbInserted(uint16_t code)
{
  ssd1306_setpos(3, 7);
  Display::onUpdateMessage("> USB Disk inserted");
}

static void Mp3Notify::OnCardRemoved(uint16_t code)
{
  ssd1306_setpos(3, 7);
  Display::onUpdateMessage("> Card removed");
}

static void Mp3Notify::OnUsbRemoved(uint16_t code)
{
  ssd1306_setpos(3, 7);
  Display::onUpdateMessage("> USB Disk removed");
}

