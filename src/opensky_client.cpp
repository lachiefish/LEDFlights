#include <string>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#include "opensky_client.h"
#include "secrets.h"

PlaneInfo OpenSkyClient::getFirstPlaneInArea(float lamin, float lomin, float lamax, float lomax)
{
  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient https;

  if (!is_authenticated || millis() - last_auth_time >= auth_interval)
  {
    last_auth_time = millis();
    authenticate();
  }

  if (auth_token.empty())
  {
    Serial.println("[OpenSkyClient] Authentication token is empty. Cannot proceed.");
    https.end();
    return PlaneInfo{};
  }

  std::string api_url{"https://opensky-network.org/api/states/all?"};
  api_url += "lamin=" + std::to_string(lamin) +
             "&lomin=" + std::to_string(lomin) +
             "&lamax=" + std::to_string(lamax) +
             "&lomax=" + std::to_string(lomax);

  https.begin(client, api_url.c_str());
  https.addHeader("Authorization", "Bearer " + String(auth_token.c_str()));
  int httpCode = https.GET();
  Serial.print("[OpenSkyClient] HTTP Code: ");
  Serial.println(httpCode);

  PlaneInfo plane_info{};

  if (httpCode == 200)
  {
    std::string payload{https.getString().c_str()};
    Serial.print("[OpenSkyClient] Payload: ");
    Serial.println(payload.c_str());

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (!error)
    {
      JsonArray states{doc["states"]};
      if (states.size() > 0)
      {
        JsonArray first_plane{states[0]};

        plane_info.icao24 = first_plane[(int)OpenSkyStateIndex::icao24].as<std::string>();
        plane_info.callsign = first_plane[(int)OpenSkyStateIndex::callsign].as<std::string>();
        plane_info.origin_country = first_plane[(int)OpenSkyStateIndex::origin_country].as<std::string>();
        plane_info.time_position = first_plane[(int)OpenSkyStateIndex::time_position].as<int>();
        plane_info.last_contact = first_plane[(int)OpenSkyStateIndex::last_contact].as<int>();
        plane_info.longitude = first_plane[(int)OpenSkyStateIndex::longitude].as<float>();
        plane_info.latitude = first_plane[(int)OpenSkyStateIndex::latitude].as<float>();
        plane_info.baro_altitude = first_plane[(int)OpenSkyStateIndex::baro_altitude].as<float>() * 3.281; // Convert to ft
        plane_info.on_ground = first_plane[(int)OpenSkyStateIndex::on_ground].as<bool>();
        plane_info.velocity = first_plane[(int)OpenSkyStateIndex::velocity].as<float>();
        plane_info.true_track = first_plane[(int)OpenSkyStateIndex::true_track].as<float>();
        plane_info.vertical_rate = first_plane[(int)OpenSkyStateIndex::vertical_rate].as<float>();
        plane_info.geo_altitude = first_plane[(int)OpenSkyStateIndex::geo_altitude].as<float>() * 3.281; // Convert to ft
        plane_info.squawk = first_plane[(int)OpenSkyStateIndex::squawk].as<std::string>();
        plane_info.spi = first_plane[(int)OpenSkyStateIndex::spi].as<bool>();

        shortenCountry(&plane_info.origin_country);
        validatePlaneInfo(&plane_info);
      }
    }
  }
  else
  {
    Serial.print("[OpenSkyClient] HTTP error: ");
    Serial.println(httpCode);
  }

  https.end();
  return plane_info;
}

// TODO
void OpenSkyClient::validatePlaneInfo(PlaneInfo *plane_info)
{
  plane_info->callsign = plane_info->callsign == "" ? "Unknown" : plane_info->callsign;
  plane_info->squawk = plane_info->squawk == "null" ? "????" : plane_info->squawk;
}

void OpenSkyClient::shortenCountry(std::string *country)
{
  if (*country == "United States")
  {
    *country = "USA";
  }
  else if (*country == "United Arab Emirates")
  {
    *country = "UAE";
  }
  else if (*country == "New Zealand")
  {
    *country = "NZ";
  }
}

void OpenSkyClient::authenticate()
{
  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient https;
  https.begin(client, "https://auth.opensky-network.org/auth/realms/opensky-network/protocol/openid-connect/token");
  https.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String payload = "grant_type=client_credentials&client_id=" + String(OPENSKY_CLIENT_ID) + "&client_secret=" + String(OPENSKY_CLIENT_SECRET);
  int httpCode = https.POST(payload);
  Serial.print("[OpenSkyClient] HTTP Code for authentication: ");
  Serial.println(httpCode);

  if (httpCode == 200)
  {
    String response = https.getString();
    Serial.print("[OpenSkyClient] Auth response: ");
    Serial.println(response);

    int start = response.indexOf("access_token\":\"") + 15;
    int end = response.indexOf("\"", start);
    auth_token = response.substring(start, end).c_str();
    Serial.print("[OpenSkyClient] Auth token: ");
    Serial.println(auth_token.c_str());
    is_authenticated = true;
  }
  else
  {
    Serial.print("[OpenSkyClient] Authentication failed with code: ");
    Serial.println(httpCode);
    is_authenticated = false;
  }

  https.end();
}