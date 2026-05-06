# ESP32 UART Loopback (ESP-IDF)

## Overview
This project implements UART communication on the ESP32 using ESP-IDF.  
It reads incoming serial data and echoes it back using a loopback mechanism.

## Background
UART (Universal Asynchronous Receiver-Transmitter) is a serial communication protocol that uses two lines:
- TX (Transmit)
- RX (Receive)

It operates asynchronously without a clock signal.  
This project uses standard **115200 baud, 8N1 format**.

## ESP32 UART Usage
- UART0 → Used for flashing and debugging (not used here)
- UART1 → Used for this project

## Features
- UART1 configuration using ESP-IDF driver
- RX/TX handled via ring buffers
- Interrupt-driven data reception
- Real-time echo functionality

## Pin Configuration
- TX → GPIO17  
- RX → GPIO16  

## Working Principle
1. UART driver is initialized with baud rate and frame format
2. GPIO pins are mapped using GPIO matrix
3. Driver installs RX/TX buffers
4. Application continuously:
   - reads incoming data
   - writes it back to UART

## Hardware Required
- ESP32 DevKit (ESP-WROOM-32)
- USB-to-Serial Adapter

## How to Run
```bash
idf.py build flash monitor