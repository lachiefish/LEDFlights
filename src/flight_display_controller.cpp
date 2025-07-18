#include "flight_display_controller.h"
#include "config.h"

FlightDisplayController::FlightDisplayController(NetworkManager &wifi, LEDDisplay &display, TimeManager &time_manager, ConfigManager &config_manager)
    : wifi(wifi), display(display), time_manager(time_manager), config_manager(config_manager) {}

void FlightDisplayController::setup()
{
  Serial.begin(9600);

  config_manager.begin();

  display.printRowText("Connecting", 0);
  display.printRowText("to wifi", 1);
  wifi.connect();

  display.printRowText("Getting", 0);
  display.printRowText("local time", 1);
  time_manager.begin(UTC_OFFSET, DST_OFFSET, NTP_SERVER_1, NTP_SERVER_2);

  display.printRowText("Starting", 0);
  display.printRowText("web server", 1);

  wifi.startMDNS();
  wifi.startWebServer();

  display.printRowText("Connecting", 0);
  display.printRowText("to plane", 1);
  display.printRowText("database", 2);

  last_api_ping = millis() - API_REFRESH_INTERVAL_MS;
}

void FlightDisplayController::loop()
{
  wifi.ensureConnected();
  wifi.webServerLoop();

  if (time_manager.isQuietHour(NIGHT_HOUR_START, NIGHT_HOUR_END))
  {
    display.clearScreen();
    display.flipBuffer();
    delay(900000);
    return;
  }

  unsigned long now = millis();

  if (now - last_api_ping >= API_REFRESH_INTERVAL_MS)
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
  display.flipBuffer();
}

void FlightDisplayController::updatePlaneInfo()
{
  api_task_running = true;
  Serial.println((time_manager.getLocalTimeString() + " Starting apiTask").c_str());
  xTaskCreatePinnedToCore(
      apiTask,   // Task function
      "ApiTask", // Name
      8192,      // Stack size
      this,      // Parameter
      1,         // Priority
      NULL,      // Task handle
      1);
}

void FlightDisplayController::showPlaneInfo()
{
  display.printRowText(last_plane.callsign, 0);
  display.printRowText(last_plane.origin_country, 1);
  display.printRowText(static_cast<float>(roundf(last_plane.geo_altitude * 100) / 100), 2, "ft");
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
  auto *self = static_cast<FlightDisplayController *>(parameter);

  OpenSkyClient client;
  PlaneInfo plane = client.getFirstPlaneInArea(GEO_LAMIN, GEO_LOMIN, GEO_LAMAX, GEO_LOMAX);
  self->last_plane = plane;
  self->is_plane_available = !plane.on_ground;
  self->api_task_running = false;
  vTaskDelete(NULL);
}