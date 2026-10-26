#pragma once
#include <Arduino.h>
#include "imu_monitor.h"

enum class EmergencyEvent { NONE, POSSIBLE_FALL, PROLONGED_INACTIVITY, HEALTH_WARNING, SENSOR_FAULT };
const char* eventToString(EmergencyEvent event);

class EmergencyManager {
 public:
  void begin();
  EmergencyEvent update(const MotionSample &motion, bool wearHint, bool imuReady, uint32_t now);
  uint32_t inactivitySeconds(uint32_t now) const;
 private:
  uint32_t lastMotionMs = 0;
  uint32_t lastAlertMs = 0;
  bool inactivityAlertSent = false;
};
