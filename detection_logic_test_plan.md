# Detection logic test plan

Use synthetic inputs before hardware trials.

1. Motion samples with small changes: timer should continue.
2. Motion sample above threshold: inactivity timestamp should reset.
3. PIR low: no inactivity event should be emitted from the wear-hint path.
4. PIR high + no movement for configured timeout: one `PROLONGED_INACTIVITY` event.
5. Candidate acceleration magnitude: `POSSIBLE_FALL` label, clearly treated as heuristic.
6. IMU not initialized: `SENSOR_FAULT`.
7. Invalid health values: packet carries `-1`, not a fabricated reading.
8. Invalid/stale GPS: packet has `gps_valid=0`.
9. Receiver receives the same worker/sequence twice: duplicate ignored.

Current firmware is a starting point for testing, not a complete safety validation. Expand automated unit tests before relying on any event detection.
