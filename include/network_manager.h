#pragma once

#include <string>
#include <WiFiManager.h>

#include "config_manager.h"
#include <vector>

class NetworkManager
{
private:
  WiFiManager wifi_manager;
  ConfigManager &config_manager;

  std::vector<WiFiManagerParameter *> custom_parameters;

  unsigned long last_reconnect_attempt = 0;
  const unsigned long reconnect_interval = 5000;

  void saveConfigCallback();
  void createCustomParameters();
  void addCustomParameters();
  void updateConfigFromCustomParameters();

public:
  NetworkManager(ConfigManager &config_manager);
  void connect();
  void ensureConnected();
  void webServerLoop();
  void disconnect();
  bool isConnected();
  std::string getCurrentSSID();
  void startWebServer();
  void startMDNS();
};