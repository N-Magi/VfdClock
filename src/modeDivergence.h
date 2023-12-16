#pragma once

#include "modeBase.h"
#include "buildParam.h"


class ModeDivergence : public ModeBase
{
public:
    void exec();

private:
    ulong elapsed_time;
    bool isdivergence = false;
    int8_t phase;
    void procKeys();
};