# LoRa-Based-Offline-Emergency-Messaging-System
Offline LoRa-based emergency communication system for disaster and no-network zones

This project implements a low-cost, infrastructure-free emergency communication system using LoRa technology.

## Problem Statement
During disasters such as floods, earthquakes, or terrorist attacks, mobile networks often fail, leaving victims and first responders without communication.

## Proposed Solution
A standalone, portable, two-way messaging system that works without internet or cellular networks using LoRa peer-to-peer communication.

## Hardware Components
- ESP32 Microcontroller
- LoRa Module (433 MHz)
- 4x4 Matrix Keypad
- I2C 16x2 LCD Display
- Antenna

## Working Principle
- Devices remains in listening mode by default
- On keypad press, a predefined emergency message is transmitted
- All nearby systems within the range return immediately to receive mode and display the message
- CRC and SyncWord ensure reliable communication

## Applications
- Disaster response communication
- Emergency rescue coordination
- No-network or remote areas

## Future Scope 
- To implement environmental sensors for emergency alerts
- To use Solar Power instead of batteries
