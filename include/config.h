#pragma once

#include <string>

// Time
static const float UTC_OFFSET{10}; // Offset in hours
static const float DST_OFFSET{0};  // Daylight savings offset in hours
static const std::string NTP_SERVER_1{"time.google.com"};
static const std::string NTP_SERVER_2{"pool.ntp.org"};

// Quiet Hours
static const int NIGHT_HOUR_START{21}; // 9:00 PM
static const int NIGHT_HOUR_END{8};    // 8:00 AM

// API
static const float GEO_LAMIN{-33.890000}; // North Sydney
static const float GEO_LOMIN{151.080000};
static const float GEO_LAMAX{-33.730000};
static const float GEO_LOMAX{151.250000};

// LED Matrix
static const int PANEL_WIDTH{64};
static const int PANEL_HEIGHT{32};
static const int PANEL_CHAIN{1};

static const int PANEL_BRIGHTNESS{255}; // 0–255

// Update Frequency
static const int API_REFRESH_INTERVAL_MS{120000};