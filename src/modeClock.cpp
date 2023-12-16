#include "modeClock.h"

void ModeClock::exec()
{

    procKeys();

    TimeData times = _rtc->getTime();
    uint8_t swState = _brd->getBtnStat();

    ushort date[8] = {times.year / 10u, times.year % 10u, 10u, times.month / 10u, times.month % 10u, 10u, times.day / 10u, times.day % 10u};

    ushort time1[8] = {times.hour / 10u, times.hour % 10u, 10u, times.min / 10u, times.min % 10u, 10u, times.sec / 10u, times.sec % 10u};
    createData(time1, date);
    _brd->setDiplsayData(md);
    _brd->render();
}

void ModeClock::procKeys()
{

    uint8_t btn = _brd->getBtnStat();

    bool accept = bitRead(btn, 7);
    bool back = bitRead(btn, 6);

    if (accept)
    {
        *_modeStat = DIVERGENCE;
        return;
    }

    if (back)
    {
        if (_net->isConnected())
        {   
            *_modeStat = NTPADJUSTMENT;
            return;
        }
        *_modeStat = ADJUSTMENT;
        return;
    }
}