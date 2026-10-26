# Calibration guide

- Establish a baseline IMU noise level with the board stationary on a bench.
- Tune motion thresholds using recorded and labeled data; do not copy a threshold blindly between mounting positions.
- Begin with a short inactivity timeout for bench testing, then restore the documented operational setting.
- Validate MAX30102 readings against an appropriate reference under controlled conditions; do not use the prototype for medical decisions.
- Test GPS outdoors with a clear view of the sky and track fix age.
- Verify the radio using two nodes in a permitted band with antennas attached as required by the module.
- Treat all thresholds as prototype settings, not validated safety limits.
