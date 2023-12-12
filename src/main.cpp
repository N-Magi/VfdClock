
#include <Arduino.h>
#include <SPI.h>
#include <CliTerminal.h>
#include "board.h"
#include "matrixData.h"
#include "RX8900.h"
#include "timeData.h"
#include "FlashConfig.h"
#include "network.h"
#include <time.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "modeBase.h"
#include "modeClock.h"

#define METHOD_PCS 10

//Define. 50 is Console Charactor maximum Length 
Cli_Terminal terminal(50);

//method prototype
void method(String str);
Board brd;
FlashConfig config;
RX8900 rtc;
Network net(&config);
ModeBase mode[10];
MatrixData md[9];

enum ModeStat
{
    ADJUSTMENT = 3,
    CLOCK = 1,
    DIVERGENCE = 2,
    NTPADJUSTMENT = 4
} modeState;




bool render(repeating_timer_t *rt){
  brd.render();

  return true;
}

void setup() {
  
  Serial.begin(9600);
  
  brd.init();
  rtc.setup();
  config.loadData();
  net.connect();
  TimeData times = net.getTime("ntp.nict.jp");
  rtc.setTime(times);

  ModeClock mc;

  mode[0] = mc;

  static repeating_timer timer;

}

void loop() {

  TimeData times = rtc.getTime();
  uint8_t swState = brd.getBtnStat;

  ushort date[8] = {times.year / 10u, times.year % 10u, 10u, times.month / 10u, times.month % 10u, 10u , times.day /10u, times.day % 10u};

  ushort time1[8] = {times.hour / 10u, times.hour % 10u, 10u, times.min / 10u, times.min % 10u, 10u, times.sec / 10u, times.sec % 10u};
  createData(time1,date);
  brd.setDiplsayData(md);
  brd.render();

}


