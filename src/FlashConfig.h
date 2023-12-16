#pragma once

#include <hardware/flash.h>
#include <hardware/sync.h>
#include "config.h"

#define FLASH_TARGET_OFFSET 0x1f0000

class FlashConfig
{
public:
    void loadData();
    void saveData();

    Config ssid;
    Config pass;
    Config ntpAddr;

private:
    uint writeData(uint8_t *data, Config config, uint startIdx);
};
