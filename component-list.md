# Component list

| Component | Function | Verification needed |
|---|---|---|
| Arduino Nano RP2040 Connect | Controller and onboard IMU | Exact board and board package |
| PIR module | Infrared motion hint | Output voltage, field of view |
| MAX30102 breakout | Pulse and SpO₂ estimates | Breakout regulator/level shifting and algorithm validation |
| NEO-6M | GNSS location | UART pins, antenna, fix behavior |
| SX1278 / compatible SX127x | Raw LoRa radio | Exact model, frequency, antenna, regional rules |
| Battery and regulator | Power | Current budget, cell protection, regulator thermal rating |
| Optional wear sensor | Helmet-wear detection | Choose contact/pressure/proximity device |
| Optional buzzer/button | Local warning/cancel | Current and pin configuration |
