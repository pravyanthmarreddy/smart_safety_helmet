#pragma once

// PROVISIONAL configuration. Verify the exact board pinout and module before wiring.
#define WORKER_ID "WORKER_001"

// Raw-LoRa frequency in MHz. This is a PLACEHOLDER, not a recommendation.
// Set only after confirming your radio module and legal regional parameters.
#define LORA_FREQUENCY_MHZ 433.0

#define LORA_CS_PIN 10
#define LORA_RESET_PIN 9
#define LORA_DIO0_PIN 2

#define PIR_PIN 3
#define BUZZER_PIN 4       // optional; firmware currently only uses serial warnings
#define CANCEL_BUTTON_PIN 5 // optional; not active unless physically wired and enabled

#define GPS_BAUD 9600
#define SERIAL_BAUD 115200

// Thresholds are initial prototype values and must be calibrated with logged data.
#define INACTIVITY_TIMEOUT_MS 60000UL
#define STATUS_INTERVAL_MS 10000UL
#define SENSOR_POLL_INTERVAL_MS 100UL
#define GPS_MAX_AGE_MS 5000UL

// A simple IMU magnitude-change threshold; not a validated fall detector.
#define MOTION_DELTA_THRESHOLD 0.18f
#define CANDIDATE_FALL_ACCEL_G 2.5f

// If true, PIR HIGH is treated as a rough motion/occupancy hint, NOT proof of wear.
#define USE_PIR_AS_WEAR_HINT true
