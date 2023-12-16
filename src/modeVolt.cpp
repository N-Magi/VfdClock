#include "modeVolt.h"

void ModeVolt::exec()
{
    procKeys();
    int v18 = 2800 * analogRead(27) * 3.3 / (1 << 10);
    int v21 = 2800 * analogRead(26) * 3.3 / (1 << 10);
    ushort date[8] = {11, 11, 11, 11, v21 / 1000, (v21 % 1000) / 100, (v21 % 100) / 10, v21 % 10};
    ushort time1[8] = {11, 11, 11, 11, v18 / 1000, (v18 % 1000) / 100, (v18 % 100) / 10, v18 % 10};
    createData(time1, date);
    md[5].dp18 = true;
    md[5].dp21 = true;
    _brd->setDiplsayData(md);
    _brd->render();
}

void ModeVolt::procKeys()
{
    uint8_t btn = _brd->getBtnStat();

    bool accept = bitRead(btn, 7);
    bool back = bitRead(btn, 6);

    if (back)
    {

        *_modeStat = DIVERGENCE;
        return;
    }
}