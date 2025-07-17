#include "network_manager.h"

NetworkManager::NetworkManager()
{
}

void NetworkManager::connectWiFiManager()
{
  // wifi_manager.resetSettings();
  bool result;
  result = wifi_manager.autoConnect("LEDFlights WiFi");
  if (!result)
  {
    Serial.println("[WiFiManager] Failed to connect.");
    ESP.restart();
  }
  else
  {
    Serial.println("[WiFiManager] Connected to WiFi.");
  }
}

void NetworkManager::ensureConnectedWiFiManager()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("[WifiManager] Lost connection. Attempting to reconnect");
    wifi_manager.setConfigPortalBlocking(false);
    wifi_manager.autoConnect("LEDFlights WiFi");
  }
}

void NetworkManager::disconnect()
{
  WiFi.disconnect();
  Serial.println("[WIFI] Disconnected");
}

bool NetworkManager::isConnected()
{
  Serial.print("[WIFI] Status: ");
  Serial.println(WiFi.status());
  return WiFi.status() == WL_CONNECTED ? true : false;
}

std::string NetworkManager::getCurrentSSID()
{
  return std::string(WiFi.SSID().c_str());
}