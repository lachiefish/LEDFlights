#pragma once

#include "network_manager.h"
#include "led_display.h"
#include "time_manager.h"
#include "opensky_client.h"
#include "config_manager.h"

class FlightDisplayController
{
public:
  FlightDisplayController(NetworkManager &wifi, LEDDisplay &display, TimeManager &time_manager, ConfigManager &config_manager);

  void setup();
  void loop();

private:
  NetworkManager &wifi;
  LEDDisplay &display;
  TimeManager &time_manager;
  ConfigManager &config_manager;

  unsigned long last_api_ping{0};
  unsigned long last_time_update{0};
  PlaneInfo last_plane;
  bool is_plane_available = false;
  bool api_task_running = false;

  void updatePlaneInfo();
  void showPlaneInfo();
  void showTime();
  static void apiTask(void *parameter);
};