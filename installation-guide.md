# Installation guide

1. Install Arduino IDE 2.x.
2. Install the Arduino Nano RP2040 Connect board support.
3. Install libraries: `Arduino_LSM6DSOX`, SparkFun MAX3010x, `TinyGPSPlus`, and Sandeep Mistry `LoRa`.
4. Open the transmitter sketch in `firmware/helmet_transmitter/`.
5. Confirm board, port, SPI pins, UART mapping, sensor wiring, and radio frequency before upload.
6. Compile with radio disabled first, then test sensors individually.
7. Repeat for `firmware/control_room_receiver/` on a second compatible radio node.

Library APIs may change. If compilation fails, record the exact error and installed library versions before changing code.
