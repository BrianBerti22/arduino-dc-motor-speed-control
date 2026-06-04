# DC Motor Speed Control using Arduino

## Overview

This project implements speed control of a DC motor using an Arduino Uno, PWM modulation and an incremental encoder for speed measurement.

The system was developed as part of a Control Theory laboratory project and includes both open-loop and closed-loop operation modes.

The project allows real-time monitoring of motor speed (RPM), PWM duty cycle and controller behavior through the Serial Monitor.

---

## Features

- PWM motor speed control
- Open-loop operation
- Closed-loop speed regulation
- Incremental encoder feedback
- Real-time RPM measurement
- Serial monitoring and data logging
- Experimental response analysis
- Transient response evaluation

---

## Hardware Used

- Arduino Uno
- DC Motor
- Incremental Encoder
- IRFZ44N MOSFET
- Flyback Diode (1N4007)
- Potentiometer
- Breadboard
- External Power Supply

---

## System Architecture

Potentiometer → Arduino → PWM → MOSFET → DC Motor

Encoder → Arduino → RPM Measurement → Controller

---

## Experimental Results

### Open-Loop Test

The motor speed was evaluated using different PWM duty cycles.

| Duty Cycle (%) | RPM |
|---------------|------|
| 30 | 6700 |
| 40 | 8600 |
| 50 | 9700 |
| 60 | 10400 |
| 70 | 11000 |
| 80 | 11300 |
| 90 | 11600 |
| 100 | 12100 |

The results show a direct relationship between PWM duty cycle and motor speed.

---

### Closed-Loop Test

A closed-loop controller was implemented using encoder feedback.

Setpoint:

1000 RPM

The controller automatically adjusted the PWM signal to reach and maintain the desired speed.

The transient response, overshoot and stabilization process were analyzed experimentally.

---

## Repository Structure

```

arduino-dc-motor-speed-control

├── control_motor.ino
├── images
├── data
├── docs
├── LICENSE
└── README.md

```

---

## Technologies

- Arduino IDE
- C++
- PWM Control
- Control Systems
- Embedded Systems
- Electronics
- Data Acquisition

---

## Future Improvements

- PI Controller
- PID Controller
- OLED Interface
- Current Monitoring
- ESP32 Migration
- Wireless Monitoring

---

## Author

Brian Berti

Electronics Technician Student – Automation Orientation
