# Low-Cost Torsion Testing & Torque Estimation Platform (Prototype)

## Overview

This project is a prototype torsion testing platform developed to explore low-cost torque–angle measurement for material twisting experiments.

The system integrates a geared DC motor, encoder-based angular measurement, and current sensing to estimate applied torque and study torsional behavior of specimens.

Rather than a fully calibrated industrial testing machine, this platform focuses on validating the **architecture required for torque estimation and angular displacement measurement** in a compact embedded system.

The prototype was developed as a third-semester academic project and serves as a foundation for future calibrated material testing.

---

## Core Capabilities (Prototype Stage)

* Controlled torsional loading using geared DC motor
* Angular displacement measurement via encoder
* Real-time current sensing using ACS712
* Serial monitoring of angle and electrical parameters
* Physical torsion testing of flexible specimens (wire tests)

---

## System Specifications

| Parameter          | Value                                  |
| ------------------ | -------------------------------------- |
| Motor              | 12V high-torque geared DC motor        |
| Gear Ratio         | 26.87:1                                |
| Encoder Resolution | 100 line wheel (~800 PPR effective)    |
| Current Sensor     | ACS712 (30A)                           |
| Motor Driver       | BTS7960 high-current driver            |
| Frame              | Wooden structure with L-brackets       |
| Control            | Microcontroller-based (embedded C/C++) |
| Measurement Output | Serial monitor                         |

---

# Why this project exists

Commercial torsion testing machines are expensive and inaccessible for most student labs.
This project was built to explore whether torsional load estimation and angular measurement could be achieved using:

* Motor current sensing
* Encoder-based angle measurement
* Embedded control system

The objective was to prototype a **low-cost torsion testing architecture** capable of applying controlled twisting force and estimating torque using electrical parameters.

The project focuses on validating measurement methodology rather than producing certified material data.

---

# System Architecture

## Mechanical Structure

* One end driven by geared DC motor
* Opposite end fixed clamp
* Specimen mounted between drive and fixed ends
* Wooden structural frame with metal L-brackets

The setup enables controlled twisting of specimens while measuring angular displacement.

---

## Drive System

**Motor:**

* 12V geared DC motor
* High torque output via gearbox
* Suitable for slow controlled torsion

**Driver:**

* BTS7960 high-current motor driver
* Enables bidirectional torque application
* Stable under load

---

## Sensing System

### Angle Measurement

* Photoelectric encoder wheel
* 100-line resolution
* Tracks angular displacement of rotating shaft
* Provides real-time rotational data

### Current Measurement

* ACS712 30A current sensor
* Measures motor current consumption
* Used as indirect torque estimation parameter

Torque estimation model:

> Motor torque ∝ armature current × motor torque constant (Kt)

This approach enables torque approximation without dedicated torque sensor.

---

## Control & Output

* Microcontroller-based control system
* Serial monitor output for:

  * Angular displacement
  * Electrical parameters
* Prototype torque estimation logic implemented

---

# Prototype Testing

### Physical Validation

The system successfully demonstrated torsional deformation on flexible specimens such as:

* 16 AWG silicone wire (~18 cm length)

Observed:

* Controlled twisting
* Measurable angular displacement
* Stable motor operation

This validated the mechanical and sensing architecture of the platform.

---

# Current Limitations (Important)

This is an early-stage prototype and not a calibrated testing instrument.

### Calibration

* Motor torque constant (Kt) not experimentally derived
* Torque values currently estimation-based
* No certified torque sensor validation

### Mechanical

* Final shaft couplings pending
* Limited rigid specimen testing
* Frame suitable for light/medium testing only

### Data Validation

* Current-to-torque mapping not fully validated
* Requires controlled calibration experiments
* No material strength dataset generated yet

---

# Engineering Insights

* Motor current sensing provides viable low-cost torque estimation path
* Encoder-based angular measurement enables torsion analysis
* Mechanical alignment critical for accurate testing
* Coupling quality directly affects torque transmission
* Calibration is essential for real material data

---

# Future Development

* Precision shaft couplings
* Motor torque constant calibration
* Real torque vs current characterization
* Data logging and graph generation
* Testing on aluminium and steel specimens
* Rigid metal frame redesign
* Optional load cell torque sensing


This decision affects internship perception heavily.
