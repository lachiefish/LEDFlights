#include <ESPmDNS.h>

#include "network_manager.h"

NetworkManager::NetworkManager()
{
}

void NetworkManager::connect()
{
  // wifi_manager.resetSettings();
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