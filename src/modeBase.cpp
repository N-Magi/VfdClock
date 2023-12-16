#include "modeBase.h"

void ModeBase::init(RX8900 *rtc, FlashConfig *config, Board *brd, ModeState *modeStat, Network *net)
{
    _rtc = rtc;
    _config = config;
    _brd = brd;
    _modeStat = modeStat;
    _net = net;
};

void ModeBase::createData(ushort *data18, ushort *data21)
{
    ushort num18[4], num21[4];
    for (int idx = 7; idx >= 0; idx--)
    {

        num18[0] = 7 - idx;
        num18[1] = data18[idx];
        num21[0] = 7 - idx;
        num21[1] = data21[idx];

        md[idx] = MatrixData::generateMatrixData(num18, num21);
    }

    num18[0] = 0;
    num18[1] = 11;
    num21[0] = 0;
    num21[1] = 11;
    md[8] = MatrixData::generateMatrixData(num18, num21);
}