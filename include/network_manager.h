#pragma once

#include <string>
#include <WiFiManager.h>

class NetworkManager
{
private:
  WiFiManager wifi_manager;

  unsigned long last_reconnect_attempt = 0;
  const unsigned long reconnect_interval = 5000;

public:
  NetworkManager();
  void connect();
  void ensureConnected();
  void webServerLoop();
  void disconnect();
  bool isConnected();
  std::string getCurrentSSID();
  void startWebServer();
  void startMDNS();
};