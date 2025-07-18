#include <Arduino.h>
#include <ctime>

#include "time_manager.h"

void TimeManager::begin(std::string timezone_rules, std::string ntp1, std::string ntp2)
{
  Serial.println("[TIME] Setting local time");
  const std::string tz = "AEST-10AEDT-11,M10.1.0/2,M4.1.0/3"; // Sydney timezone with DST rules
  configTzTime(tz.c_str(), ntp1.c_str(), ntp2.c_str());
  while (time(nullptr) < 100000)
  {
    delay(100); // Wait until time is synced
  }
  Serial.println("[TIME] Time is set");
}

int TimeManager::getHour()
{
  time_t now = time(nullptr);
  struct tm *timeinfo = localtime(&now);
  // Serial.print("[TIME] Hour is: ");
  // Serial.println(timeinfo->tm_hour);
  return timeinfo ? timeinfo->tm_hour : -1;
}

bool TimeManager::isQuietHour(int night_start, int night_end)
{
  int hour = getHour();
  if (hour == -1)
  {
    return false; // Time is not set somehow
  }
  if (night_start > night_end)
  {
    return (hour >= night_start || hour < night_end);
  }
  else
  {
    return (hour >= night_start && hour < night_end);
  }
}

std::string TimeManager::getLocalTimeString()
{
  time_t now = time(nullptr);
  struct tm *timeinfo = localtime(&now);
  if (timeinfo)
  {
    char buf[9]; // HH:MM:SS\0
    snprintf(buf, sizeof(buf), "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    return std::string(buf);
  }
  else
  {
    return "--:--:--";
  }
}

// TODO
std::string TimeManager::getLocalDayString()
{
  time_t now = time(nullptr);
  struct tm *timeinfo = localtime(&now);
  if (timeinfo)
  {
    char buf[9]; // Monday - Sunday\0
    strftime(buf, sizeof(buf), "%A", timeinfo);
    return std::string(buf);
  }
  else
  {
    return "--------";
  }
}

std::string TimeManager::getLocalDateString()
{
  time_t now = time(nullptr);
  struct tm *timeinfo = localtime(&now);
  if (timeinfo)
  {
    char buf[11]; // DD/MM/YYYY\0
    strftime(buf, sizeof(buf), "%d/%m/%Y", timeinfo);
    return std::string(buf);
  }
  else
  {
    return "---";
  }
}

std::string TimeManager::getLocalMonthShortString()
{
  time_t now = time(nullptr);
  struct tm *timeinfo = localtime(&now);
  if (timeinfo)
  {
    char buf[4]; // Jan - Dec\0
    strftime(buf, sizeof(buf), "%b", timeinfo);
    return std::string(buf);
  }
  else
  {
    return "---";
  }
}

std::string TimeManager::getLocalYearString()
{
  time_t now = time(nullptr);
  struct tm *timeinfo = localtime(&now);
  if (timeinfo)
  {
    char buf[5]; // Jan - Dec
    strftime(buf, sizeof(buf), "%Y", timeinfo);
    return std::string(buf);
  }
  else
  {
    return "----";
  }
}