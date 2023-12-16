#include "modeNtpAdjust.h"

void ModeNtpAdjust::exec()
{
    procKeys();

    TimeData _time;
    _time = _rtc->getTime();
    ushort date[8] = {_time.year / 10u, _time.year % 10u, 10u, _time.month / 10u, _time.month % 10u, 10u, _time.day / 10u, _time.day % 10u};
    ushort time1[8] = {_time.hour / 10u, _time.hour % 10u, 10u, _time.min / 10u, _time.min % 10u, 10u, _time.sec / 10u, _time.sec % 10u};
    
    if (millis() % ADJUST_BLINKING_PERIOD_MS <= (ADJUST_BLINKING_PERIOD_MS / 2))
    {
        for (int idx = 0; idx < sizeof(date); idx++){
            date[idx] = 11u;
            time1[idx] = 11u;
        }
    }

    createData(time1, date);
    _brd->setDiplsayData(md);
    _brd->render();
}

void ModeNtpAdjust::procKeys()
{
    uint8_t btn = _brd->getBtnStat();
    bool accept = bitRead(btn, 7);
    bool back = bitRead(btn, 6);
    bool plus = bitRead(btn, 5);
    bool minus = bitRead(btn, 4);

    if (accept)
    {
        _rtc->setTime(_net->getTime(NTP_SRV));
        *_modeStat = ModeState::CLOCK;
    }

    if (back)
    {
        *_modeStat = ModeState::ADJUSTMENT;
    }
}