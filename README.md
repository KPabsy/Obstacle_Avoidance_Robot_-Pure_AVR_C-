# Autonomous Obstacle Avoidance Robot (Pure AVR C)

This repository contains the source code for an autonomous robot car designed for **Obstacle Avoidance**. It is written in **Pure AVR C** for the ATmega328P (Arduino Uno), interacting directly with hardware registers to handle motor control and sensor inputs.

## 🤖 How It Works
The robot uses three Infrared (IR) sensors to scan for obstacles. Its primary behavior is to move forward until an obstacle is detected, at which point it executes a pre-programmed turn to avoid a collision.

### Detection Scenarios:
* **Center Wall:** If only the front sensor is triggered, the robot stops and pivots 90° to the left.
* **Left Obstacle:** If a wall is detected on the left, the robot pivots 90° to the right.
* **Right Obstacle:** If a wall is detected on the right, the robot pivots 90° to the left.
* **Corners:** If both front and a side sensor are triggered, the robot pivots in the opposite direction to escape.



## 🛠️ Hardware Setup

| Component | Arduino Pin | Register/Port |
| :--- | :--- | :--- |
| **Center IR Sensor** | Pin 2 | `PIND2` |
| **Right IR Sensor** | Pin 3 | `PIND3` |
| **Left IR Sensor** | Pin 12 | `PINB4` |
| **Motor A Speed (ENA)** | Pin 6 | `OC0A` (PWM) |
| **Motor B Speed (ENB)** | Pin 5 | `OC0B` (PWM) |
| **IN1 / IN2 (Left Motor)** | Pin 9 / 8 | `PB1` / `PB0` |
| **IN3 / IN4 (Right Motor)**| Pin 7 / 4 | `PD7` / `PD4` |



## ⚙️ Calibration Constants
The following values in `main.c` can be tuned for your specific hardware:

* `FORWARD_SPEED`: Sets the cruising speed (0-255).
* `TURN_SPEED`: Sets the power during a 90° pivot.
* `TURN_90_MS`: Adjust this duration (in milliseconds) to ensure the robot completes a perfect 90° turn on your specific floor surface.

## 🚀 How to Use
1. **Wire the Hardware:** Follow the pin mapping table provided above. Ensure the L298N and Arduino share a common Ground.
2. **Remove Jumpers:** Remove the ENA/ENB jumpers on the L298N board to allow PWM speed control.
3. **Upload:** Open the code in the Arduino IDE and upload it to your Uno.
4. **Tune Sensors:** Use the potentiometers on the IR sensors to set the detection range (recommended 10-15cm).

---
*Note: This code is optimized for the ATmega328P. Using other boards may require register re-mapping.*
