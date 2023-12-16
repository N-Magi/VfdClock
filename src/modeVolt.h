#pragma once

#include "modeBase.h"
#include "buildParam.h"


class ModeVolt : public ModeBase
{
public:
    void exec();

private:
    void procKeys();
};