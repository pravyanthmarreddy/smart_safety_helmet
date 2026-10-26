# System architecture

```mermaid
flowchart TB
  subgraph Helmet
    IMU[LSM6DSOX] --> MCU[Nano RP2040 Connect]
    PIR[PIR motion hint] --> MCU
    PPG[MAX30102] --> MCU
    GNSS[NEO-6M] --> MCU
    MCU --> FSM[Event state logic]
    FSM --> LORA[SX127x raw LoRa]
  end
  LORA -. radio packets .-> RXLORA[Receiver radio]
  RXLORA --> RXMCU[Receiver controller]
  RXMCU --> LOG[Serial log / operator]
```

All pin assignments and the radio frequency are provisional until the exact modules and board pinout are verified.

# Troubleshooting

- **IMU initialization fails:** verify the exact Nano RP2040 Connect board, board package, I²C wiring if applicable, and `Arduino_LSM6DSOX` version.
- **MAX30102 unavailable:** verify I²C wiring, breakout voltage requirements, address, and library example.
- **No GPS fix:** test outdoors; confirm UART mapping and baud rate; never substitute fake coordinates.
- **LoRa init fails:** confirm exact radio family, SPI pin mapping, CS/RESET/DIO0, antenna, and library compatibility.
- **Receiver sees nothing:** match frequency and radio settings exactly, use compatible modules, and check local radio rules.
- **Compiler says `Serial1` or a pin is unsupported:** verify board selection and core pin mapping; do not assume another Nano variant has the same mapping.
- **Unreliable health values:** mark them invalid and review optical contact, movement, ambient light, and algorithm limitations.
