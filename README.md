# Smart Home Energy Saver 

The **General Electric Saving System** is a comprehensive smart-home automation and security solution designed to optimize residential energy consumption while ensuring rigorous physical safety. Developed as a graduation project for the **Information Technology Institute (ITI) Embedded Systems** track, this project leverages a distributed dual-microcontroller architecture to seamlessly balance environmental automation, remote monitoring, and access control.

##  System Architecture
The system is built on a dual-MCU setup to prevent processing bottlenecks, separating security logic from environmental automation.
*   **Microcontrollers:** 2× AVR ATmega32
*   **Intra-System Communication:** Synchronized local state over **I2C**
*   **Wireless Communication:** Bluetooth module interfaced via **UART** on the primary MCU

##  Key Features

###  Smart Energy Management
*   **Occupancy-Based Lighting:** Dual IR sensors keep an active count of room occupants, dynamically scaling indoor lighting to eliminate energy waste in empty rooms.
*   **Ambient Light Automation:** An LDR sensor monitors external light levels to automatically toggle outdoor lighting at dawn and dusk.
*   **Climate Control:** Automated temperature-based cooling fans adjust dynamically to room conditions.

###  Security & Hazard Detection
*   **Secure Access Control:** A Keypad and LCD interface handles entry authentication, preventing unauthorized access.
*   **Fire & Gas Alarms:** Integrated gas and flame sensors continuously monitor the environment, triggering a loud hardware alarm for real-time hazard alerting.

###  Remote & Local Monitoring
*   **Wireless Control:** Complete remote monitoring and control of the entire house via a Bluetooth-enabled smartphone connection.
*   **Master Diagnostic Panel:** A dedicated local master control panel provides real-time diagnostic feedback and system status from both ATmega32 units.

##  Technologies & Hardware Used
*   **MCUs:** AVR ATmega32
*   **Protocols:** I2C, UART
*   **Sensors:** LDR (Light), IR (Motion/Occupancy), LM35 (Temperature), MQ-2 (Gas), Flame Sensor
*   **Actuators/Outputs:** LCD (16x2), Keypad (4x4), LEDs, DC Motors (Fans), Buzzers, Bluetooth Module (HC-05/HC-06)