#include "network_manager.h"

NetworkManager::NetworkManager(std::string ssid, std::string password) : ssid(ssid), password(password)
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
  }
  else
  {
    Serial.println("[WiFiManager] Connected to WiFi.");
  }
  wifi_manager.setConfigPortalBlocking(false);
}

void NetworkManager::ensureConnectedWiFiManager()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("[WifiManager] Lost connection. Attempting to reconnect");
    wifi_manager.autoConnect("LEDFlights WiFi");
  }
}

void NetworkManager::connect()
{
  Serial.print("[WIFI] Attempting to connect, SSID: ");
  Serial.println(ssid.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(ssid.c_str(), password.c_str());
    delay(1000);
  }
  Serial.print("[WIFI] Connected, SSID: ");
  Serial.println(ssid.c_str());
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

void NetworkManager::ensureConnected()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    unsigned long now = millis();
    if (now - last_reconnect_attempt >= reconnect_interval)
    {
      Serial.println("[WIFI] Lost connection. Attempting to reconnect");
      WiFi.disconnect();
      WiFi.begin(ssid.c_str(), password.c_str());
      last_reconnect_attempt = now;
    }
  }
}

std::string NetworkManager::getCurrentSSID()
{
  return std::string(WiFi.SSID().c_str());
}