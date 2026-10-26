# Circuit connections (provisional)

Do not wire from this document alone. Verify each module's exact datasheet, board pinout, and voltage requirements.

| Module signal | Proposed controller signal | Status |
|---|---|---|
| MAX30102 SDA/SCL | Board I²C SDA/SCL | Confirm breakout voltage and bus compatibility |
| GPS TX | `Serial1` RX (often D0 on Nano-style layout) | Verify core pin mapping |
| GPS RX | `Serial1` TX (often D1) | Optional |
| SX127x NSS/CS | D10 | Provisional |
| SX127x RESET | D9 | Provisional |
| SX127x DIO0 | D2 | Provisional |
| SX127x MOSI/MISO/SCK | Board SPI pins | Verify actual SPI pin mapping |
| PIR OUT | D3 | Must be 3.3 V-safe |
| Optional buzzer | D4 via suitable driver | Not enabled in base firmware |
| Optional cancel button | D5 to GND, `INPUT_PULLUP` | Not enabled in base firmware |

The onboard IMU and MAX30102 may share the I²C bus if their addresses do not conflict. Do not connect 5 V signals to 3.3 V-only GPIO.
