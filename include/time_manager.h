#pragma once

#include <string>

class TimeManager
{
private:
public:
  void begin(float utc_offset, float dst_offset, std::string ntp1, std::string ntp2);
  int getHour();
  bool isQuietHour(int night_start, int night_end);
  std::string getLocalTimeString();
  std::string getLocalDayString();
  std::string getLocalMonthShortString();
  std::string getLocalYearString();
  std::string getLocalDateString();
};