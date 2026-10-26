/*
  Smart Safety Helmet - provisional transmitter sketch.
  Board assumption: Arduino Nano RP2040 Connect.
  Radio assumption: raw SX127x LoRa module supported by Sandeep Mistry LoRa library.
  Verify every pin, voltage level, and frequency before connecting/transmitting.
*/
#include <Wire.h>
#include <Arduino_LSM6DSOX.h>
#include <MAX30105.h>
#include <heartRate.h>
#include <spo2_algorithm.h>
#include <TinyGPSPlus.h>
#include <LoRa.h>
#include "config.h"
#include "imu_monitor.h"
#include "gps_manager.h"
#include "lora_communication.h"
#include "emergency_manager.h"

MAX30105 particleSensor;
TinyGPSPlus gps;
ImuMonitor imuMonitor;
GpsManager gpsManager;
EmergencyManager emergencyManager;
LoRaCommunication radioLink;

static uint32_t lastStatusMs = 0;
static uint32_t sequenceNumber = 0;
static bool imuReady = false;
static bool maxReady = false;
static bool loraReady = false;
static int heartRateBpm = -1;
static int spo2Percent = -1;

void readHealthSensor() {
  if (!maxReady) { heartRateBpm = -1; spo2Percent = -1; return; }
  // The library's example algorithm is not a clinical algorithm. We intentionally
  // keep values invalid until a separate validated measurement routine is integrated.
  long ir = particleSensor.getIR();
  if (ir < 50000) {
    heartRateBpm = -1;
    spo2Percent = -1;
  } else {
    // TODO: integrate and validate the SparkFun example's full red/IR buffer algorithm.
    // Never present a placeholder as a measurement.
    heartRateBpm = -1;
    spo2Percent = -1;
  }
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  uint32_t waitStart = millis();
  while (!Serial && millis() - waitStart < 3000) { }

  pinMode(PIR_PIN, INPUT);
  Serial.println("[BOOT] Smart Safety Helmet prototype");
  Wire.begin();

  imuReady = IMU.begin();
  Serial.println(imuReady ? "[IMU] initialized" : "[FAULT] IMU initialization failed");

  maxReady = particleSensor.begin(Wire, I2C_SPEED_FAST);
  if (maxReady) {
    particleSensor.setup();
    particleSensor.setPulseAmplitudeRed(0x1F);
    particleSensor.setPulseAmplitudeIR(0x1F);
    Serial.println("[MAX30102] initialized; readings remain invalid until validated algorithm is integrated");
  } else {
    Serial.println("[FAULT] MAX30102 not detected");
  }

  Serial1.begin(GPS_BAUD);
  Serial.println("[GPS] UART started; waiting for valid fix");

  LoRa.setPins(LORA_CS_PIN, LORA_RESET_PIN, LORA_DIO0_PIN);
  loraReady = LoRa.begin(LORA_FREQUENCY_MHZ * 1000000L);
  Serial.println(loraReady ? "[LoRa] initialized - verify legal frequency" : "[FAULT] LoRa initialization failed");

  imuMonitor.begin();
  gpsManager.begin();
  emergencyManager.begin();
}

void loop() {
  const uint32_t now = millis();

  // Keep draining GPS serial data so TinyGPSPlus can maintain fix validity.
  while (Serial1.available()) {
    gps.encode(Serial1.read());
  }
  gpsManager.update(gps, now);

  MotionSample motion = {};
  if (imuReady && IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    float ax, ay, az, gx, gy, gz;
    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);
    motion = imuMonitor.update(ax, ay, az, gx, gy, gz, now);
  }

  const bool pirActive = digitalRead(PIR_PIN) == HIGH;
  const bool wearHint = USE_PIR_AS_WEAR_HINT ? pirActive : false;
  readHealthSensor();

  EmergencyEvent event = emergencyManager.update(motion, wearHint, imuReady, now);
  if (!imuReady) event = EmergencyEvent::SENSOR_FAULT;

  if (event != EmergencyEvent::NONE && loraReady) {
    const String packet = radioLink.makePacket(
      ++sequenceNumber, WORKER_ID, event, wearHint,
      heartRateBpm, spo2Percent, gpsManager.latitude(), gpsManager.longitude(),
      gpsManager.valid(), emergencyManager.inactivitySeconds(now));
    Serial.print("[ALERT] "); Serial.println(eventToString(event));
    Serial.print("[TX] "); Serial.println(packet);
    radioLink.send(packet);
  }

  if (now - lastStatusMs >= STATUS_INTERVAL_MS) {
    lastStatusMs = now;
    Serial.print("[STATUS] worn_hint="); Serial.print(wearHint ? 1 : 0);
    Serial.print(" motion="); Serial.print(motion.active ? "ACTIVE" : "QUIET");
    Serial.print(" hr="); Serial.print(heartRateBpm);
    Serial.print(" spo2="); Serial.print(spo2Percent);
    Serial.print(" gps="); Serial.println(gpsManager.valid() ? "VALID" : "GPS_UNAVAILABLE");

    if (loraReady) {
      const String packet = radioLink.makePacket(
        ++sequenceNumber, WORKER_ID, EmergencyEvent::NONE, wearHint,
        heartRateBpm, spo2Percent, gpsManager.latitude(), gpsManager.longitude(),
        gpsManager.valid(), emergencyManager.inactivitySeconds(now));
      radioLink.send(packet);
    }
  }
}
