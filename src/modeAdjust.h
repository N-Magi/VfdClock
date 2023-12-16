#pragma once

#include "modeBase.h"

class ModeAdjust : public ModeBase
{
public:
    // void init(RX8900 *rtc, FlashConfig *config, Board *brd);
    void exec();
    TimeData _time;
    ~ModeAdjust();

private:
    uint8_t _selectIdx;
    uint8_t idx = 1;
    uint8_t addTime(uint8_t time, uint8_t min, uint8_t max, int8_t amount);
    void procKeys();
};