# Testing and validation

| Test | Safe method | Pass condition |
|---|---|---|
| Normal movement | Gently move board on bench | Motion timestamp updates |
| Not worn / PIR quiet | Toggle PIR input or simulate value | No claim that wear is confirmed |
| Inactivity | Unit-test timer with shortened duration | Correct event label emitted |
| Candidate fall | Inject synthetic IMU samples | Candidate event only; no validation claim |
| Invalid MAX30102 | Disconnect during bench test | Values marked invalid |
| GPS unavailable | Indoor test / disconnect safely | `gps_valid=0` |
| Packet loss | Turn receiver off during test | Missing reception is recognized as a limitation |
| Duplicate packet | Replay sequence number | Receiver ignores duplicate |
| Sensor initialization failure | Disconnect one sensor before boot | Error is logged and code avoids fake readings |
| False-alarm cancellation | Only if button is physically wired and implemented | Cancellation works before deployment |
| Recovery | Restore radio after interruption | Subsequent packets are received |

Use simulated inputs first. Never stage a real fall or expose a person to a hazard to test the prototype. Independent validation is required before safety-critical use.
