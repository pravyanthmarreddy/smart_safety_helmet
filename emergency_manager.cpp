#include "emergency_manager.h"
#include "config.h"

const char* eventToString(EmergencyEvent event) {
  switch (event) {
    case EmergencyEvent::POSSIBLE_FALL: return "POSSIBLE_FALL";
    case EmergencyEvent::PROLONGED_INACTIVITY: return "PROLONGED_INACTIVITY";
    case EmergencyEvent::HEALTH_WARNING: return "HEALTH_WARNING";
    case EmergencyEvent::SENSOR_FAULT: return "SENSOR_FAULT";
    default: return "STATUS";
  }
}

void EmergencyManager::begin() {
  lastMotionMs = millis();
  lastAlertMs = 0;
  inactivityAlertSent = false;
}

EmergencyEvent EmergencyManager::update(const MotionSample &motion, bool wearHint, bool imuReady, uint32_t now) {
  if (!imuReady) return EmergencyEvent::SENSOR_FAULT;
  if (motion.active) {
    lastMotionMs = now;
    inactivityAlertSent = false;
  }
  // Candidate-fall event is a simple heuristic only and is not a validated detector.
  if (motion.candidateFall && now - lastAlertMs > 3000UL) {
    lastAlertMs = now;
    return EmergencyEvent::POSSIBLE_FALL;
  }
  if (wearHint && !motion.active && !inactivityAlertSent &&
      now - lastMotionMs >= INACTIVITY_TIMEOUT_MS) {
    inactivityAlertSent = true;
    lastAlertMs = now;
    return EmergencyEvent::PROLONGED_INACTIVITY;
  }
  return EmergencyEvent::NONE;
}

uint32_t EmergencyManager::inactivitySeconds(uint32_t now) const {
  return (now - lastMotionMs) / 1000UL;
}
