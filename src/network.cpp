#include "Network.h"

Network::Network(FlashConfig *config)
{
  _config = config;
}

bool Network::isConnected()
{

  return WiFi.isConnected() & (WiFi.getMode() != WIFI_AP);
}

bool Network::connect(char *ssid, char *pass)
{
  // Connect Wifi
  WiFi.disconnect(false);
  WiFi.mode(WIFI_STA);
  if (sizeof(ssid) > 0)
    WiFi.begin(ssid, pass);
  // WiFi.begin();
  Serial.print("Try Connect WiFi:");
  Serial.println(ssid);
  uint16_t time = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("=");
    delay(250);
    if (time + 500 <= millis())
    {
      Serial.println("TIMEOUT!!!");
      break;
    }
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Connected!!");
    return true;
  }
  return false;
}

TimeData Network::getTime(char *url)
{
  NTP.begin(url);
  NTP.waitSet();

  t = time(NULL) + (3600 * 9);
  tms = localtime(&t);

  TimeData timed;
  timed.year = tms->tm_year % 100;
  timed.month = tms->tm_mon + 1;
  timed.day = tms->tm_mday;
  timed.hour = tms->tm_hour;
  timed.min = tms->tm_min;
  timed.sec = tms->tm_sec;
  return timed;
}

bool Network::connect()
{
  if (_config->ssid.configSize <= 0)
  {
    return false;
  }
  return connect(_config->ssid.config , _config->pass.config);
}
