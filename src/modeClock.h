#pragma once
#include "modeBase.h"

class ModeClock : ModeBase{
    public:
        void exec();

    private:
        void createData(ushort *data18, ushort *data21);
        MatrixData md[9];
}