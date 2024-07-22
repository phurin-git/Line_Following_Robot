# Line Following Robot
This project involves creating a line-following robot using an Arduino UNO microcontroller and PID algorithm. The robot is designed to detect and follow a line, typically a black line on a white surface, using infrared sensors.
## Features

- **Infrared Sensors:** Utilizes IR sensors to detect the line and adjust the robot's path.
- **Arduino Control:** Employs an Arduino board for processing sensor inputs and controlling the motors.
- **Motor Drivers:** Uses motor drivers to manage the movement of the robot's wheels.
- **Responsive Navigation:** Capable of making real-time adjustments to follow curved paths and intersections.
## Components
- Arduino Uno
- Infrared line sensors
- L298N motor driver
- DC motors and wheels
- Chassis
- Power supply (battery pack)
- Connecting wires and breadboard
## How it works
- **Sensor Input:** The infrared sensors detect the presence of the line by measuring reflected light. A black line reflects less light, while a white surface reflects more.
- **Processing:** The Arduino reads the sensor inputs and determines the position of the line relative to the robot.
- **Control:** Based on the sensor readings, the Arduino sends signals to the motor driver to adjust the speed and direction of the motors, ensuring the robot stays on the line.
## Getting Started
- **Hardware Setup:** Assemble the components as per the wiring diagram provided.
- **Software:** Upload the Arduino code to the board using the Arduino IDE.
- **Testing:** Place the robot on a track and observe its line-following behavior. Adjust sensor sensitivity and control parameters as needed.