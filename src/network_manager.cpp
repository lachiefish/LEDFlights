#include <ESPmDNS.h>

#include "network_manager.h"

NetworkManager::NetworkManager(ConfigManager &config_manager) : config_manager(config_manager)
{
}

void NetworkManager::saveConfigCallback()
{
  Serial.println("[NetworkManager] Configuration saved");
}

void NetworkManager::createCustomParameters()
{
  custom_parameters.clear();
  custom_parameters.push_back(new WiFiManagerParameter("latitude_min", "Latitude Min", std::to_string(config_manager.getLatitudeMin()).c_str(), 10));
  custom_parameters.push_back(new WiFiManagerParameter("latitude_max", "Latitude Max", std::to_string(config_manager.getLatitudeMax()).c_str(), 10));
  custom_parameters.push_back(new WiFiManagerParameter("longitude_min", "Longitude Min", std::to_string(config_manager.getLongitudeMin()).c_str(), 10));
  custom_parameters.push_back(new WiFiManagerParameter("longitude_max", "Longitude Max", std::to_string(config_manager.getLongitudeMax()).c_str(), 10));
  custom_parameters.push_back(new WiFiManagerParameter("quiet_hour_start", "Quiet Hour Start", std::to_string(config_manager.getQuietHourStart()).c_str(), 3));
  custom_parameters.push_back(new WiFiManagerParameter("quiet_hour_end", "Quiet Hour End", std::to_string(config_manager.getQuietHourEnd()).c_str(), 3));
  custom_parameters.push_back(new WiFiManagerParameter("brightness", "Brightness", std::to_string(config_manager.getBrightness()).c_str(), 3));
  custom_parameters.push_back(new WiFiManagerParameter("ntp_server_1", "NTP Server 1", config_manager.getNtpServer1().c_str(), config_manager.getNtpServer1().length()));
  custom_parameters.push_back(new WiFiManagerParameter("ntp_server_2", "NTP Server 2", config_manager.getNtpServer2().c_str(), config_manager.getNtpServer2().length()));
  custom_parameters.push_back(new WiFiManagerParameter("timezone_rules", "Timezone Rules", config_manager.getTimezoneRules().c_str(), config_manager.getTimezoneRules().length()));
  custom_parameters.push_back(new WiFiManagerParameter("api_refresh_interval_ms", "API Refresh Interval (ms)", std::to_string(config_manager.getApiRefreshIntervalMs()).c_str(), 10));
}

void NetworkManager::updateConfigFromCustomParameters()
{
}

void NetworkManager::addCustomParameters()
{
  for (auto parameter : custom_parameters)
  {
    wifi_manager.addParameter(parameter);
  }
}

void NetworkManager::connect()
{
  // wifi_manager.resetSettings();
  createCustomParameters();
  WiFi.setHostname("ledflights");
  bool result;
  result = wifi_manager.autoConnect("LEDFlights WiFi");
  if (!result)
  {
    Serial.println("[NetworkManager] Failed to connect");
    ESP.restart();
  }
  else
  {
    Serial.println("[NetworkManager] Connected to WiFi");
  }
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, IPAddress(1, 1, 1, 1), IPAddress(1, 0, 0, 1));
}

void NetworkManager::ensureConnected()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("[NetworkManager] Lost connection. Attempting to reconnect");
    wifi_manager.autoConnect("LEDFlights WiFi");
  }
}

void NetworkManager::webServerLoop()
{
  wifi_manager.process();
}

void NetworkManager::disconnect()
{
  WiFi.disconnect();
  Serial.println("[NetworkManager] Disconnected");
}

bool NetworkManager::isConnected()
{
  Serial.print("[NetworkManager] Status: ");
  Serial.println(WiFi.status());
  return WiFi.status() == WL_CONNECTED ? true : false;
}

std::string NetworkManager::getCurrentSSID()
{
  return std::string(WiFi.SSID().c_str());
}

void NetworkManager::startMDNS()
{
  if (!MDNS.begin("ledflights"))
  {
    Serial.println("[NetworkManager] Error starting mDNS");
  }
}

void NetworkManager::startWebServer()
{
  wifi_manager.setParamsPage(true);
  wifi_manager.setConfigPortalBlocking(false);
  wifi_manager.startWebPortal();
}