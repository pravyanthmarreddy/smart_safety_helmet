#pragma once
#include <Arduino.h>
#include <TinyGPSPlus.h>

class GpsManager {
 public:
  void begin();
  void update(TinyGPSPlus &gps, uint32_t now);
  bool valid() const;
  double latitude() const;
  double longitude() const;
 private:
  bool fixValid = false;
  double lat = 0.0;
  double lon = 0.0;
  uint32_t lastFixMs = 0;
};
