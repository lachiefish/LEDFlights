#include "config_manager.h"

void ConfigManager::begin()
{
  prefs.begin("ledflights", false);
  load();
}

void ConfigManager::load()
{
  latitude_min = prefs.getFloat("latitude_min", latitude_min);
  latitude_max = prefs.getFloat("latitude_max", latitude_max);
  longitude_min = prefs.getFloat("longitude_min", longitude_min);
  longitude_max = prefs.getFloat("longitude_max", longitude_max);
  quiet_hour_start = prefs.getInt("quiet_hour_start", quiet_hour_start);
  quiet_hour_end = prefs.getInt("quiet_hour_end", quiet_hour_end);
  brightness = prefs.getInt("brightness", brightness);
  ntp_server_1 = prefs.getString("ntp_server_1", ntp_server_1.c_str()).c_str();
  ntp_server_2 = prefs.getString("ntp_server_2", ntp_server_2.c_str()).c_str();
  timezone_rules = prefs.getString("timezone_rules", timezone_rules.c_str()).c_str();
  api_refresh_interval_ms = prefs.getInt("api_refresh_interval_ms", api_refresh_interval_ms);
}

void ConfigManager::save()
{
  prefs.putFloat("latitude_min", latitude_min);
  prefs.putFloat("latitude_max", latitude_max);
  prefs.putFloat("longitude_min", longitude_min);
  prefs.putFloat("longitude_max", longitude_max);
  prefs.putInt("quiet_hour_start", quiet_hour_start);
  prefs.putInt("quiet_hour_end", quiet_hour_end);
  prefs.putInt("brightness", brightness);
  prefs.putString("ntp_server_1", ntp_server_1.c_str());
  prefs.putString("ntp_server_2", ntp_server_2.c_str());
  prefs.putString("timezone_rules", timezone_rules.c_str());
  prefs.putInt("api_refresh_interval_ms", api_refresh_interval_ms);
}

void ConfigManager::end()
{
  prefs.end();
}

float ConfigManager::getLatitudeMin() { return latitude_min; }
float ConfigManager::getLatitudeMax() { return latitude_max; }
float ConfigManager::getLongitudeMin() { return longitude_min; }
float ConfigManager::getLongitudeMax() { return longitude_max; }
int ConfigManager::getQuietHourStart() { return quiet_hour_start; }
int ConfigManager::getQuietHourEnd() { return quiet_hour_end; }
int ConfigManager::getBrightness() { return brightness; }
std::string ConfigManager::getNtpServer1() { return ntp_server_1; }
std::string ConfigManager::getNtpServer2() { return ntp_server_2; }
std::string ConfigManager::getTimezoneRules() { return timezone_rules; }
int ConfigManager::getApiRefreshIntervalMs() { return api_refresh_interval_ms; }

void ConfigManager::setLatitudeMin(float val) { latitude_min = val; }
void ConfigManager::setLatitudeMax(float val) { latitude_max = val; }
void ConfigManager::setLongitudeMin(float val) { longitude_min = val; }
void ConfigManager::setLongitudeMax(float val) { longitude_max = val; }
void ConfigManager::setQuietHourStart(int val) { quiet_hour_start = val; }
void ConfigManager::setQuietHourEnd(int val) { quiet_hour_end = val; }
void ConfigManager::setBrightness(int val) { brightness = val; }
void ConfigManager::setNtpServer1(std::string val) { ntp_server_1 = val; }
void ConfigManager::setNtpServer2(std::string val) { ntp_server_2 = val; }
void ConfigManager::setTimezoneRules(std::string val) { timezone_rules = val; }
void ConfigManager::setApiRefreshIntervalMs(int val) { api_refresh_interval_ms = val; }
