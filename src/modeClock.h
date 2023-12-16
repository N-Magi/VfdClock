#pragma once
#include "modeBase.h"
#include "board.h"
#include "matrixData.h"
#include "RX8900.h"
#include "timeData.h"
#include "FlashConfig.h"
#include "network.h"

class ModeClock : public ModeBase
{
public:
    // void init(RX8900 *rtc, FlashConfig *config, Board *brd);
    void exec();

private:
    // RX8900 *_rtc;
    // FlashConfig *_config;
    // Board *_brd;
    // MatrixData md[9];

    void procKeys();
};