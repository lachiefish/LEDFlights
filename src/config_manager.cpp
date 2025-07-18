#include "config_manager.h"

void ConfigManager::begin()
{
  prefs.begin("ledflights", false);
  load();
  createCustomParameters();
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

void ConfigManager::addCustomParametersToWiFiManager(WiFiManager &wifi_manager)
{
  for (auto parameter : custom_parameters)
  {
    wifi_manager.addParameter(parameter);
  }
}

void ConfigManager::createCustomParameters()
{
  custom_parameters.clear();
  custom_parameters.push_back(new WiFiManagerParameter("latitude_min", "Latitude Min", std::to_string(latitude_min).c_str(), 10));
  custom_parameters.push_back(new WiFiManagerParameter("latitude_max", "Latitude Max", std::to_string(latitude_max).c_str(), 10));
  custom_parameters.push_back(new WiFiManagerParameter("longitude_min", "Longitude Min", std::to_string(longitude_min).c_str(), 10));
  custom_parameters.push_back(new WiFiManagerParameter("longitude_max", "Longitude Max", std::to_string(longitude_max).c_str(), 10));
  custom_parameters.push_back(new WiFiManagerParameter("quiet_hour_start", "Quiet Hour Start", std::to_string(quiet_hour_start).c_str(), 3));
  custom_parameters.push_back(new WiFiManagerParameter("quiet_hour_end", "Quiet Hour End", std::to_string(quiet_hour_end).c_str(), 3));
  custom_parameters.push_back(new WiFiManagerParameter("brightness", "Brightness", std::to_string(brightness).c_str(), 3));
  custom_parameters.push_back(new WiFiManagerParameter("ntp_server_1", "NTP Server 1", ntp_server_1.c_str(), ntp_server_1.length()));
  custom_parameters.push_back(new WiFiManagerParameter("ntp_server_2", "NTP Server 2", ntp_server_2.c_str(), ntp_server_2.length()));
  custom_parameters.push_back(new WiFiManagerParameter("timezone_rules", "Timezone Rules", timezone_rules.c_str(), timezone_rules.length()));
  custom_parameters.push_back(new WiFiManagerParameter("api_refresh_interval_ms", "API Refresh Interval (ms)", std::to_string(api_refresh_interval_ms).c_str(), 10));
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
void ConfigManager::setNtpServer1(std::string &val) { ntp_server_1 = val; }
void ConfigManager::setNtpServer2(std::string &val) { ntp_server_2 = val; }
void ConfigManager::setTimezoneRules(std::string &val) { timezone_rules = val; }
void ConfigManager::setApiRefreshIntervalMs(int val) { api_refresh_interval_ms = val; }
