#pragma once

#include <string>
#include <vector>

struct PlaneInfo
{
  std::string icao24 = "";
  std::string callsign = "";
  std::string origin_country = "";
  int time_position = -1;
  int last_contact = -1;
  float longitude = -1.0;
  float latitude = -1.0;
  float baro_altitude = -1.0;
  bool on_ground = true;
  float velocity = -1.0;
  float true_track = -1.0;
  float vertical_rate = 0;
  std::vector<int> sensors; // Not implemented
  float geo_altitude = -1;
  std::string squawk = "";
  bool spi = false;
  int position_source = 0; // Not implemented
};

enum class OpenSkyStateIndex
{
  icao24,          // string
  callsign,        // string
  origin_country,  // string
  time_position,   // int
  last_contact,    // int
  longitude,       // float
  latitude,        // float
  baro_altitude,   // float
  on_ground,       // boolean
  velocity,        // float
  true_track,      // float
  vertical_rate,   // float
  sensors,         // int[]
  geo_altitude,    // float
  squawk,          // string
  spi,             // boolean
  position_source, // int
};

class OpenSkyClient
{
private:
  bool is_authenticated = false;
  unsigned long last_auth_time = 0;
  unsigned long auth_interval = 1800000; // 30 minutes in milliseconds
  std::string auth_token = "";

  void shortenCountry(std::string *country);
  void validatePlaneInfo(PlaneInfo *plane_info);
  void authenticate();

public:
  PlaneInfo getFirstPlaneInArea(float lamin, float lomin, float lamax, float lomax);
};