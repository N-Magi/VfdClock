#pragma once

#include "modeBase.h"

#define NTP_SRV "ntp.nict.jp"

class ModeNtpAdjust : public ModeBase
{
private:
    void procKeys();
public:
    void exec();
};