#pragma once

#include <string>
#include <WiFiManager.h>

class NetworkManager
{
private:
  std::string ssid;
  std::string password;

  WiFiManager wifi_manager;

  unsigned long last_reconnect_attempt = 0;
  const unsigned long reconnect_interval = 5000;

public:
  NetworkManager();
  void connectWiFiManager();
  void ensureConnectedWiFiManager();
  void disconnect();
  bool isConnected();
  std::string getCurrentSSID();
};