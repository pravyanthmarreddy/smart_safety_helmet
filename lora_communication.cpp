#include "lora_communication.h"
#include "config.h"
#include <LoRa.h>

String LoRaCommunication::makePacket(uint32_t seq, const char *workerId, EmergencyEvent event,
                                     bool wearHint, int heartRate, int spo2, double lat, double lon,
                                     bool gpsValid, uint32_t inactivitySeconds) {
  String p = "SH1,";
  p += String(seq); p += ",";
  p += workerId; p += ",";
  p += eventToString(event); p += ",";
  p += String(wearHint ? 1 : 0); p += ",";
  p += String(heartRate); p += ",";
  p += String(spo2); p += ",";
  p += String(gpsValid ? lat : 0.0, 6); p += ",";
  p += String(gpsValid ? lon : 0.0, 6); p += ",";
  p += String(gpsValid ? 1 : 0); p += ",";
  p += String(inactivitySeconds);
  return p;
}

bool LoRaCommunication::send(const String &packet) {
  LoRa.beginPacket();
  LoRa.print(packet);
  return LoRa.endPacket() == 1;
}
