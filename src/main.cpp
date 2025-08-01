#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#include "config_manager.h"
#include "time_manager.h"
#include "network_manager.h"
#include "opensky_client.h"
#include "led_display.h"
#include "flight_display_controller.h"

#define PANEL_WIDTH 64
#define PANEL_HEIGHT 32
#define PANEL_CHAIN 1

ConfigManager config_manager;
NetworkManager wifi{config_manager};
LEDDisplay display{HUB75_I2S_CFG(PANEL_WIDTH, PANEL_HEIGHT, PANEL_CHAIN)};
TimeManager time_manager;

FlightDisplayController controller{wifi, display, time_manager, config_manager};

void setup()
{
  controller.setup();
}

void loop()
{
  controller.loop();
}