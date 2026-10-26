#pragma once
#include <Arduino.h>
#include "emergency_manager.h"

class LoRaCommunication {
 public:
  String makePacket(uint32_t seq, const char *workerId, EmergencyEvent event,
                    bool wearHint, int heartRate, int spo2, double lat, double lon,
                    bool gpsValid, uint32_t inactivitySeconds);
  bool send(const String &packet);
};
