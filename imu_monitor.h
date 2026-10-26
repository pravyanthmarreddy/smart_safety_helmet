#pragma once
#include <Arduino.h>

struct MotionSample {
  bool active;
  bool candidateFall;
  float accelMagnitudeG;
};

class ImuMonitor {
 public:
  void begin();
  MotionSample update(float ax, float ay, float az, float gx, float gy, float gz, uint32_t now);
 private:
  float previousMagnitude = 1.0f;
  uint32_t lastMotionMs = 0;
};
