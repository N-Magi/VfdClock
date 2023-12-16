#pragma once

#include "board.h"
#include "matrixData.h"
#include "RX8900.h"
#include "timeData.h"
#include "FlashConfig.h"
#include "network.h"
#include "ModeState.h"
#include "buildParam.h"

class ModeBase
{
public:
    void init(RX8900 *rtc, FlashConfig *config, Board *brd, ModeState *modeStat, Network *net);

protected:
    ModeState *_modeStat;
    RX8900 *_rtc;
    FlashConfig *_config;
    Board *_brd;
    Network *_net;
    MatrixData md[9];
    
    

    void createData(ushort *data18, ushort *data21);
    //void procKeys();
};
