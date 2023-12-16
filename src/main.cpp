// Library
#include <Arduino.h>
#include <SPI.h>
#include <CliTerminal.h>
#include <time.h>
#include <WiFi.h>
#include <FastLED.h>
// Utility
#include "board.h"
#include "matrixData.h"
#include "RX8900.h"
#include "timeData.h"
#include "FlashConfig.h"
// mode
#include "ModeState.h"
#include "modeClock.h"
#include "modeAdjust.h"
#include "modeNtpAdjust.h"
#include "modeDivergence.h"
#include "modeVolt.h"
// Network
#include "network.h"
#include <WiFiClient.h>
#include <DNSServer.h>
#include <WebServer.h>

#define METHOD_PCS 10

#define DATA_PIN 6
#define NUM_LEDS 2
CRGB leds[NUM_LEDS];
// Define. 50 is Console Charactor maximum Length
Cli_Terminal terminal(50);

ModeState mode = ModeState::CLOCK;

Board brd;
FlashConfig config;
RX8900 rtc;
Network net(&config);

ModeClock modeClock;
ModeAdjust modeAdjust;
ModeNtpAdjust modeNtpAdjust;
ModeDivergence modeDivergence;
ModeVolt modeVolt;

String getRes = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>HTML Form to Input Data</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <h2>HTML Form to Input Data</h2> 
  <form action="/" method = "post">
    <input type="text", name="ssid", placeholder="ssid"><br/>
    <input type="text", name="pass", placeholder="password"><br/>
    <input type="submit" name="submit" value="SET">
  </form>
</body></html>)rawliteral";

const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;
WebServer webServer(80);

void setup()
{
  Serial.begin(9600);
  brd.init();
  rtc.setup();
  config.loadData();

  if (bitRead(brd.getBtnStat(), 3))
  {
    config.ssid.config = nullptr;
    config.ssid.configSize = 0;
    config.pass.config = nullptr;
    config.pass.configSize = 0;
    config.saveData();
  }

  if (config.ssid.configSize <= 0)
  {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("VFD CLOCK NETWORK SETTINGS");

    dnsServer.start(DNS_PORT, "*", apIP);

    webServer.onNotFound([]()
                         {
     webServer.send(301, "text/html", "Redirect To Setting Page");
    webServer.sendHeader("Location", "http://172.217.28.1/"); });
    webServer.begin();
    webServer.on(Uri("/"), HTTP_GET, []()
                 { webServer.send(200, "text/html", getRes); });
    webServer.on(Uri("/"), HTTP_POST, []()
                 {
                   arduino::String ssid = webServer.arg("ssid");
                   // Serial.println(ssid);
                   char ssidBuf[ssid.length() + 1];
                   ssid.toCharArray(ssidBuf, sizeof(ssidBuf), 0);
                   config.ssid.config = ssidBuf;
                   config.ssid.configSize = sizeof(ssidBuf);

                   arduino::String pass = webServer.arg("pass");
                   // Serial.println(pass);
                   char passBuf[pass.length() + 1];
                   pass.toCharArray(passBuf, sizeof(passBuf), 0);
                   config.pass.config = passBuf;
                   config.pass.configSize = sizeof(passBuf);
                   config.saveData();

                   webServer.send(200, "text/html", "succeeded");
                   webServer.close();
                   //  dnsServer.stop();
                   //  WiFi.disconnect();
                   //  WiFi.end();
                   //rp2040.reboot();
                   rp2040.rebootToBootloader();
                   });
  }
  if (config.ssid.configSize > 0)
  {
    net.connect();
    if (net.isConnected())
    {
      TimeData times = net.getTime("ntp.nict.jp");
      rtc.setTime(times);
    }
  }

  modeClock.init(&rtc, &config, &brd, &mode, &net);
  modeAdjust.init(&rtc, &config, &brd, &mode, &net);
  modeNtpAdjust.init(&rtc, &config, &brd, &mode, &net);
  modeDivergence.init(&rtc, &config, &brd, &mode, &net);
  modeVolt.init(&rtc, &config, &brd, &mode, &net);
}

void loop()
{
  dnsServer.processNextRequest();
  webServer.handleClient();

  if (mode == CLOCK)
  {
    modeClock.exec();
    modeAdjust._time = rtc.getTime();
    return;
  }
  if (mode == ADJUSTMENT)
  {
    modeAdjust.exec();
    return;
  }
  if (mode == NTPADJUSTMENT)
  {
    modeNtpAdjust.exec();
    return;
  }
  if (mode == DIVERGENCE)
  {
    modeDivergence.exec();
    return;
  }

  if (mode == VOLTAGE)
  {
    modeVolt.exec();
    return;
  }
}
