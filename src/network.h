#pragma once
#include <Arduino.h>
#include "FlashConfig.h"
#include <WiFi.h>
#include "timeData.h"


class Network
{
private:
    FlashConfig *_config;
    
public:
    struct tm *tms;
    time_t t;
    Network(FlashConfig *config);
    bool connect();
    bool connect(char *ssid, char *pass);
    TimeData getTime(char *url);
};


