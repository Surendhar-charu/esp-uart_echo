# ESP32 UART Loopback using ESP-IDF

# 📌 Project Overview

This project demonstrates UART (Universal Asynchronous Receiver-Transmitter) communication on the ESP32 using the ESP-IDF framework. The application receives serial data through UART2 and immediately echoes the received data back to the sender. The project helps in understanding low-level serial communication, ESP32 UART peripherals, ESP-IDF UART drivers, GPIO pin routing, interrupt-driven communication, and ring buffer handling.

The communication is established between the ESP32 and a PC using an external USB-to-Serial adapter. A serial terminal running on the PC sends characters to the ESP32, and the ESP32 echoes the same characters back in real time.

---

# 🧠 Background: What is UART?

UART (Universal Asynchronous Receiver-Transmitter) is one of the simplest and most widely used serial communication protocols in embedded systems. UART communication uses only two signal lines:

- TX (Transmit) → sends data
- RX (Receive) → receives data

UART is called asynchronous because it does not require a shared clock signal between devices. Instead, both devices agree on a communication speed called the baud rate before communication starts.

This project uses:

- Baud Rate: 115200
- Frame Format: 8N1

In 8N1 communication:

```text
[START][D0][D1][D2][D3][D4][D5][D6][D7][STOP]
```

- Start bit indicates the beginning of transmission
- D0–D7 represent the 8-bit data
- N means no parity bit
- 1 stop bit indicates the end of transmission

The ESP32 UART peripheral is configured with these parameters using the ESP-IDF UART driver.

---

# 🖥️ ESP32 UART Controllers

The ESP32 contains three hardware UART peripherals:

| UART | Usage |
|---|---|
| UART0 | Used for flashing and serial monitor |
| UART1 | General-purpose UART |
| UART2 | Used in this project |

UART0 is already connected internally to the onboard USB-to-Serial converter and is used by `idf.py flash` and `idf.py monitor`. To avoid conflicts with the debug console, this project uses UART2 for communication.

---

# ⚙️ ESP-IDF UART Driver

The ESP-IDF UART driver provides an abstraction layer over the hardware UART peripheral. Instead of directly accessing hardware registers, the application uses UART driver APIs provided by ESP-IDF.

When serial data arrives at the RX pin, a hardware interrupt is generated. The ESP-IDF UART driver interrupt handler stores the incoming bytes into an RX ring buffer in RAM. The application reads data from this buffer using `uart_read_bytes()`.

Similarly, outgoing data is placed into a TX ring buffer and transmitted by the UART driver in the background using `uart_write_bytes()`.

This interrupt-driven approach ensures that incoming serial data is not lost even when the application is temporarily busy.

---

# 🔧 UART Driver Initialization

UART initialization in this project follows three major steps:

## Step 1 — Configure UART Parameters

A `uart_config_t` structure is created with:

- Baud rate = 115200
- Data bits = 8
- No parity
- 1 stop bit
- Hardware flow control disabled

---

## Step 2 — Assign GPIO Pins

The ESP32 GPIO matrix allows UART peripherals to be routed to different physical GPIO pins.

This project uses:

| Function | GPIO |
|---|---|
| TX | GPIO17 |
| RX | GPIO16 |

---

## Step 3 — Install UART Driver

- Allocates RX/TX ring buffers
- Registers UART interrupt handlers
- Enables background UART communication

After this step, UART communication becomes active.

---

# 🔄 Application Working

The UART echo application continuously runs inside a FreeRTOS task.

The application loop performs the following operations:

1. Wait for incoming UART data using `uart_read_bytes()`
2. Store received data into a local buffer
3. Echo the same data back using `uart_write_bytes()`
4. Print the received string using `ESP_LOGI()`

If no data is received within the specified timeout, the loop continues waiting for new data.

This creates a real-time UART loopback system.

---

# 🔌 Hardware Connections

The ESP32 communicates with the PC using a USB-to-Serial adapter.

Connections:

```text
ESP32 GPIO17 (TX)  ─────► USB Adapter RX
ESP32 GPIO16 (RX)  ◄──── USB Adapter TX
ESP32 GND          ─────► USB Adapter GND
```

Important notes:

- TX must connect to RX
- RX must connect to TX
- Ground connection is mandatory
- ESP32 GPIO pins are 3.3V tolerant only


---

# 🛠️ ESP-IDF Functions Used

| Function | Purpose |
|---|---|
| uart_param_config() | Configure UART settings |
| uart_set_pin() | Assign TX/RX GPIO pins |
| uart_driver_install() | Install UART driver |
| uart_read_bytes() | Read UART data |
| uart_write_bytes() | Transmit UART data |

---


# 🧪 Testing

1. Connect USB-to-Serial adapter
2. Open PuTTY or another serial terminal
3. Select correct COM port
4. Set baud rate to 115200
5. Type characters in terminal
6. Observe echoed output
---

# 🚀 Learning Outcomes

This project helped in understanding:

- UART serial communication
- ESP32 UART peripherals
- ESP-IDF UART driver architecture
- Interrupt-driven communication
- Ring buffer handling
- GPIO routing using GPIO matrix
- Real-time embedded debugging
- Git and GitHub integration for embedded projects
