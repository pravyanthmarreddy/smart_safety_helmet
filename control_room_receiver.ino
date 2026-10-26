/*
  Control-room receiver prototype.
  Use a second controller + compatible raw SX127x radio.
  Match frequency and pins with the transmitter and verify regional radio rules.
*/
#include <SPI.h>
#include <LoRa.h>

#define RX_LORA_FREQUENCY_MHZ 433.0 // PLACEHOLDER: verify module and local regulations
#define RX_LORA_CS_PIN 10
#define RX_LORA_RESET_PIN 9
#define RX_LORA_DIO0_PIN 2
#define SERIAL_BAUD 115200

String lastWorker = "";
long lastSequence = -1;

void setup() {
  Serial.begin(SERIAL_BAUD);
  uint32_t start = millis();
  while (!Serial && millis() - start < 3000) {}
  LoRa.setPins(RX_LORA_CS_PIN, RX_LORA_RESET_PIN, RX_LORA_DIO0_PIN);
  if (!LoRa.begin(RX_LORA_FREQUENCY_MHZ * 1000000L)) {
    Serial.println("[FAULT] LoRa initialization failed; verify pins, module and frequency");
    while (true) delay(1000);
  }
  Serial.println("[RX] Control-room receiver ready");
}

bool validPacketShape(const String &s) {
  if (!s.startsWith("SH1,")) return false;
  int commas = 0;
  for (unsigned int i = 0; i < s.length(); ++i) if (s[i] == ',') commas++;
  return commas == 10; // 11 fields
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (!packetSize) return;

  String payload;
  while (LoRa.available()) payload += (char)LoRa.read();
  Serial.print("[RX] RSSI="); Serial.print(LoRa.packetRssi());
  Serial.print(" SNR="); Serial.println(LoRa.packetSnr());

  if (!validPacketShape(payload)) {
    Serial.println("[FAULT] Invalid packet shape; ignored");
    return;
  }

  // Parse first three fields for duplicate suppression. Full field validation is a
  // future hardening task; never treat this prototype as authenticated or secure.
  int first = payload.indexOf(',');
  int second = payload.indexOf(',', first + 1);
  int third = payload.indexOf(',', second + 1);
  String seqText = payload.substring(first + 1, second);
  String worker = payload.substring(second + 1, third);
  long seq = seqText.toInt();

  if (worker == lastWorker && seq == lastSequence) {
    Serial.println("[RX] Duplicate packet ignored");
    return;
  }
  lastWorker = worker;
  lastSequence = seq;

  Serial.print("[EVENT] ");
  Serial.println(payload);
  Serial.println("[NOTE] Radio receipt is not proof that an operator or medical help has responded.");
}
