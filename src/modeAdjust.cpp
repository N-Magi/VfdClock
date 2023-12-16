#include "modeAdjust.h"

void ModeAdjust::exec()
{

  procKeys();

  ushort date[8] = {_time.year / 10u, _time.year % 10u, 10u, _time.month / 10u, _time.month % 10u, 10u, _time.day / 10u, _time.day % 10u};
  ushort time1[8] = {_time.hour / 10u, _time.hour % 10u, 10u, _time.min / 10u, _time.min % 10u, 10u, _time.sec / 10u, _time.sec % 10u};

  if (millis() % ADJUST_BLINKING_PERIOD_MS <= (ADJUST_BLINKING_PERIOD_MS / 2))
  {
    if (_selectIdx == 0)
    {
      date[0] = 11;
      date[1] = 11;
    }
    if (_selectIdx == 1)
    {
      date[3] = 11;
      date[4] = 11;
    }
    if (_selectIdx == 2)
    {
      date[6] = 11;
      date[7] = 11;
    }
    if (_selectIdx == 3)
    {
      time1[0] = 11;
      time1[1] = 11;
    }
    if (_selectIdx == 4)
    {
      time1[3] = 11;
      time1[4] = 11;
    }
    if (_selectIdx == 5)
    {
      time1[6] = 11;
      time1[7] = 11;
    }
  }

  createData(time1, date);
  _brd->setDiplsayData(md);
  _brd->render();

  return;
}

void ModeAdjust::procKeys()
{
  uint8_t btn = _brd->getBtnStat();
  bool minus = bitRead(btn, 4) > 0;
  bool plus = bitRead(btn, 5) > 0;
  bool back = bitRead(btn, 6) > 0;
  bool accept = bitRead(btn, 7) > 0;

  if (accept)
  {

    if (_selectIdx == 5)
    {
      _rtc->setTime(_time);

      *_modeStat = CLOCK;
      Serial.println(*_modeStat);
      return;
    }

    _selectIdx++;
    return;
  }

  if (back)
  {
    if (_selectIdx == 0)
    {
      *_modeStat = CLOCK;
      return;
    }

    _selectIdx--;
    return;
  }

  if (plus)
  {

    if (_selectIdx == 0)
      _time.year =  addTime(_time.year, 0, 99, 1);
    if (_selectIdx == 1)
      _time.month = addTime(_time.month, 0, 11, 1);
    if (_selectIdx == 2)
      _time.day = addTime(_time.day, 0, 31, 1);
    if (_selectIdx == 3)
      _time.hour =  addTime(_time.hour, 0, 23, 1);
    if (_selectIdx == 4)
      _time.min =  addTime(_time.min, 0, 59, 1);
    if (_selectIdx == 5)
      _time.sec =  addTime(_time.sec, 0, 59, 1);
  }

  if (minus)
  {
    if (_selectIdx == 0)
      _time.year =  addTime(_time.year, 0, 99, -1);
    if (_selectIdx == 1)
      _time.month = addTime(_time.month, 0, 11, -1);
    if (_selectIdx == 2)
      _time.day = addTime(_time.day, 0, 31, -1);
    if (_selectIdx == 3)
      _time.hour =  addTime(_time.hour, 0, 23, -1);
    if (_selectIdx == 4)
      _time.min =  addTime(_time.min, 0, 59, -1);
    if (_selectIdx == 5)
      _time.sec =  addTime(_time.sec, 0, 59, -1);
  }
}

uint8_t ModeAdjust::addTime(uint8_t time, uint8_t min, uint8_t max, int8_t amount)
{
  if (min > time + amount)
  {
    return max;
  }
  if (max < time + amount)
  {
    return min;
  }
  return time + amount;
}