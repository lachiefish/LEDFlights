#include "flight_display_controller.h"

FlightDisplayController::FlightDisplayController(NetworkManager &wifi, LEDDisplay &display, TimeManager &time_manager, ConfigManager &config_manager)
    : wifi(wifi), display(display), time_manager(time_manager), config_manager(config_manager) {}

void FlightDisplayController::setup()
{
  Serial.begin(9600);

  config_manager.begin();

  display.setBrightness(config_manager.getBrightness());

  display.printRowText("Connecting", 0);
  display.printRowText("to wifi", 1);
  wifi.connect();

  display.printRowText("Starting", 0);
  display.printRowText("web server", 1);

  wifi.startMDNS();
  wifi.startWebServer();

  display.printRowText("Getting", 0);
  display.printRowText("local time", 1);
  time_manager.begin(config_manager.getTimezoneRules(), config_manager.getNtpServer1(), config_manager.getNtpServer2());

  display.printRowText("Connecting", 0);
  display.printRowText("to plane", 1);
  display.printRowText("database", 2);

  last_api_ping = millis() - config_manager.getApiRefreshIntervalMs();
}

void FlightDisplayController::loop()
{
  wifi.ensureConnected();
  wifi.webServerLoop();

  if (time_manager.isQuietHour(config_manager.getQuietHourStart(), config_manager.getQuietHourEnd()))
  {
    display.clearScreen();
    return;
  }

  unsigned long now = millis();

  if (now - last_api_ping >= config_manager.getApiRefreshIntervalMs() && !api_task_running)
  {
    updatePlaneInfo();
    last_api_ping = now;
  }

  if (is_plane_available)
  {
    showPlaneInfo();
  }
  else
  {
    showTime();
  }
}

void FlightDisplayController::updatePlaneInfo()
{
  api_task_running = true;
  ApiTaskParams *params = new ApiTaskParams{this, &config_manager};
  Serial.println((time_manager.getLocalTimeString() + " Starting apiTask").c_str());
  xTaskCreatePinnedToCore(
      apiTask,   // Task function
      "ApiTask", // Name
      8192,      // Stack size
      params,    // Parameter
      1,         // Priority
      NULL,      // Task handle
      1);        // Core
}

void FlightDisplayController::showPlaneInfo()
{
  display.printRowText(last_plane.callsign, 0);
  display.printRowText(last_plane.origin_country, 1);
  display.printRowText(roundf(last_plane.geo_altitude * 100) / 100, 2, "ft");
  display.printRowText("Sqk " + last_plane.squawk, 3);
}

void FlightDisplayController::showTime()
{
  unsigned long now = millis();
  if (now - last_time_update >= 200)
  {
    display.printRowText("", 0);
    display.printRowText(time_manager.getLocalTimeString(), 1, "", 8);
    display.printRowText("", 2);
    display.printRowText(time_manager.getLocalDateString(), 3, "", 2);
    last_time_update = now;
  }
}

void FlightDisplayController::apiTask(void *parameter)
{
  ApiTaskParams *params = static_cast<ApiTaskParams *>(parameter);
  FlightDisplayController *self = params->controller;
  ConfigManager *config_manager = params->config_manager;

  PlaneInfo plane = self->opensky_client.getFirstPlaneInArea(config_manager->getLatitudeMin(),
                                                             config_manager->getLongitudeMin(),
                                                             config_manager->getLatitudeMax(),
                                                             config_manager->getLongitudeMax());
  self->last_plane = plane;
  self->is_plane_available = !plane.on_ground; // Using plane.on_ground to determine availability
  self->api_task_running = false;

  delete params;
  vTaskDelete(NULL);
}