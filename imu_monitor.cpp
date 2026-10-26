#include "imu_monitor.h"
#include "config.h"
#include <math.h>

void ImuMonitor::begin() {
  previousMagnitude = 1.0f;
  lastMotionMs = millis();
}

MotionSample ImuMonitor::update(float ax, float ay, float az, float gx, float gy, float gz, uint32_t now) {
  // Arduino_LSM6DSOX acceleration values are expressed in g; gyro units depend on API.
  const float magnitude = sqrtf(ax * ax + ay * ay + az * az);
  const float delta = fabsf(magnitude - previousMagnitude);
  const bool active = delta > MOTION_DELTA_THRESHOLD || fabsf(gx) > 20.0f ||
                      fabsf(gy) > 20.0f || fabsf(gz) > 20.0f;
  const bool candidate = magnitude >= CANDIDATE_FALL_ACCEL_G;
  if (active) lastMotionMs = now;
  previousMagnitude = magnitude;
  return {active, candidate, magnitude};
}
