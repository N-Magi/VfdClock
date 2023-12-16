#include "modeDivergence.h"

void ModeDivergence::exec()
{
    procKeys();

    TimeData times = _rtc->getTime();
    uint8_t swState = _brd->getBtnStat();

    ushort date[8] = {times.year / 10u, times.year % 10u, 10u, times.month / 10u, times.month % 10u, 10u, times.day / 10u, times.day % 10u};
    ushort time1[8] = {times.hour / 10u, times.hour % 10u, 10u, times.min / 10u, times.min % 10u, 10u, times.sec / 10u, times.sec % 10u};

    if (isdivergence)
    {

        long phaseTime = (millis() - elapsed_time) - DIVERGENCE_BASE_TIME;
        phase = phaseTime / DIVERGENCE_MOVE_TIME;
        phase = (phase < 0) ? 0 : phase;
        Serial.println(phase);
        if (phase > DIVERGENCE_MAX_PHASE)
        {
            isdivergence = false;
            return;
        }

        // random化する。
        for (int cnt = 0; cnt < DIVERGENCE_MAX_PHASE - phase; cnt++)
        {

            time1[7 - cnt] = random(0, 10);
            date[7 - cnt] = random(0, 10);
        }
    }

    if (times.min % 5 == 0 & times.sec == 0)
    {
        isdivergence = true;
        elapsed_time = millis();
    }

    createData(time1, date);
    md[7].dp21 = true;
    _brd->setDiplsayData(md);
    _brd->render();
}

void ModeDivergence::procKeys()
{
    uint8_t btn = _brd->getBtnStat();

    bool accept = bitRead(btn, 7);
    bool back = bitRead(btn, 6);

    if (accept)
    {
        *_modeStat = VOLTAGE;
        return;
    }

    if (back)
    {
        
        *_modeStat = CLOCK;
        return;
    }
}