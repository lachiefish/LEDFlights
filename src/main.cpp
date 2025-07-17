#include <Arduino.h>
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#include "config.h"
#include "time_manager.h"
#include "network_manager.h"
#include "opensky_client.h"
#include "led_display.h"
#include "flight_display_controller.h"

NetworkManager wifi;
LEDDisplay display{HUB75_I2S_CFG(PANEL_WIDTH, PANEL_HEIGHT, PANEL_CHAIN)};
TimeManager time_manager;

FlightDisplayController controller{wifi, display, time_manager};

void setup()
{
  controller.setup();
}

void loop()
{
  controller.loop();
}