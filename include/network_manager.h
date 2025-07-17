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
  NetworkManager(std::string ssid, std::string password);

  void connectWiFiManager();
  void ensureConnectedWiFiManager();

  void connect();
  void disconnect();
  bool isConnected();
  void ensureConnected();
  std::string getCurrentSSID();
};