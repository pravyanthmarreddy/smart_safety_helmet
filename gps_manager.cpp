#include "gps_manager.h"
#include "config.h"

void GpsManager::begin() {
  fixValid = false; lat = 0.0; lon = 0.0; lastFixMs = 0;
}

void GpsManager::update(TinyGPSPlus &gps, uint32_t now) {
  if (gps.location.isValid() && gps.location.age() < GPS_MAX_AGE_MS) {
    lat = gps.location.lat();
    lon = gps.location.lng();
    lastFixMs = now;
    fixValid = true;
  } else if (lastFixMs == 0 || now - lastFixMs > GPS_MAX_AGE_MS) {
    fixValid = false;
  }
}

bool GpsManager::valid() const { return fixValid; }
double GpsManager::latitude() const { return fixValid ? lat : 0.0; }
double GpsManager::longitude() const { return fixValid ? lon : 0.0; }
