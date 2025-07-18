#pragma once

#include <Preferences.h>
#include <string>

class ConfigManager
{
public:
  void begin();
  void load();
  void save();

  float getLatitudeMin();
  float getLatitudeMax();
  float getLongitudeMin();
  float getLongitudeMax();
  int getQuietHourStart();
  int getQuietHourEnd();
  int getBrightness();
  std::string getNtpServer1();
  std::string getNtpServer2();
  std::string getTimezoneRules();
  int getApiRefreshIntervalMs();

  void setLatitudeMin(float val);
  void setLatitudeMax(float val);
  void setLongitudeMin(float val);
  void setLongitudeMax(float val);
  void setQuietHourStart(int val);
  void setQuietHourEnd(int val);
  void setBrightness(int val);
  void setNtpServer1(std::string &val);
  void setNtpServer2(std::string &val);
  void setTimezoneRules(std::string &val);
  void setApiRefreshIntervalMs(int val);

private:
  Preferences prefs;

  float latitude_min{-33.890000};
  float latitude_max{-33.730000};

  float longitude_min{151.080000};
  float longitude_max{151.250000};

  int quiet_hour_start{21};
  int quiet_hour_end{8};

  int brightness{255};

  // Below should not need changing

  std::string ntp_server_1{"time.google.com"};
  std::string ntp_server_2{"pool.ntp.org"};
  std::string timezone_rules{"AEST-10AEDT-11,M10.1.0/2,M4.1.0/3"};

  int api_refresh_interval_ms{120000};
};