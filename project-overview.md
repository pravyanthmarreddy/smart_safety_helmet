# Project overview

The Smart Safety Helmet is an educational prototype combining motion sensing, optional wear indication, pulse/SpO₂ estimates, GNSS, and a raw-LoRa radio link.

The prototype can report a **possible event**, not confirm an accident or diagnose a medical condition. PIR is only a motion hint and must not be treated as proof that the helmet is worn.

## Scope
- Helmet-side sensor polling and status generation.
- Heuristic inactivity and candidate-fall event labels.
- Structured radio packet to a control-room receiver.
- Bench-testing and documentation.

## Out of scope
- PPE certification, medical diagnosis, validated fall prediction, guaranteed radio delivery, or a staffed emergency response service.
