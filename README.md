# Smart_Lock


# Smart Lock System
### Overview
This project is a smart door system that uses NFC authentication or a WiFi-based web interface to unlock the door. The web interface also allows users to securely change the WiFi name and password.

### Features
Power Save Mode
The system enters a low-power state, where WiFi and other resources are disabled. The system detects sound or user input (via NFC or password) to transition to the next active state.

# Activity Mode
When motion is detected via a PIR sensor, the system prompts the user to authenticate using NFC or a password. If the authentication is successful, the lock is unlocked. After a predefined inactivity period, the system will revert to Power Save Mode.

# Web Server Mode
The system enables remote control through a web interface, allowing users to unlock the device remotely. The system returns to Power Save Mode after a set period of inactivity.

# NFC Authentication
Unlock the system using an NFC card by tapping it against the NFC reader.

# LCD Display
The LCD screen shows various messages, such as system status, prompts for NFC, password entry, and state transitions.

# RGB LED
The RGB LED provides a visual indication of the lock status: green for unlocked, red for locked, and other colors for different states.

# Servo Motor Control
The servo motor is used to physically lock or unlock the device.

# WiFi Integration
The system allows for web-based control and monitoring, enabling remote unlocking and management.

# Components Used
Arduino: The microcontroller responsible for controlling the system.
Servo Motor: Used for the physical locking mechanism.
LCD Display: Displays system status messages.
RGB LED: Provides status feedback (e.g., green for unlocked, red for locked).
NFC Reader: For NFC-based user authentication.
PIR Sensor: Detects motion to trigger state changes.
WiFi Module: Provides web server functionality for remote control.
System Flow
Power Save Mode
The system enters a low-power state by default. The system waits for sound input or user authentication via NFC or password to transition to the next mode.

# Activity Mode
The system detects motion using the PIR sensor and prompts the user to authenticate. Upon successful authentication, the system unlocks the device by moving the servo. After a set period of inactivity, the system returns to Power Save Mode.

# Web Server Mode
Users can control the lock remotely through a web interface. The system remains in Web Server Mode for a limited time, after which it reverts to Power Save Mode.

# Hardware Setup

Connect the servo motor, NFC reader, PIR sensor, LCD display, and WiFi module to the Arduino board according to the pinout specifications.
Ensure that the components are properly powered and wired to the correct pins.
# Software Setup

Download and install the necessary libraries for the servo motor, NFC reader, LCD display, WiFi module, and other components used in the project.
Upload the provided Arduino code to the board.
Modify the code to include your WiFi credentials for the web server functionality.
Usage
# Power Save Mode
After booting, the system will start in Power Save Mode. The system will detect any motion or user input (via NFC or password) and transition to Activity Mode.

# Activity Mode
Once in Activity Mode, the system will prompt the user to tap an NFC card or enter a password to unlock the lock. After the specified inactivity timeout, the system will return to Power Save Mode.

# Web Server Mode
When the system enters Web Server Mode, users can remotely control the lock through a web interface. The system will revert to Power Save Mode after a set period of inactivity.

# Future Improvements
Enhanced Security
Implement additional security features such as biometric authentication (fingerprint or facial recognition).

Mobile App Integration
Develop a mobile app for easy control and status updates.

Improved Web Interface
Enhance the web interface with more control options and monitoring features.

License
This project is open-source and licensed under the MIT License. Feel free to use, modify, and distribute the code as needed.
# Code Structure
The project is organized as follows:

- **.vscode**
  - `c_cpp_properties.json` - C/C++ IntelliSense configuration
  - `launch.json` - Debugging configuration
  - `settings.json` - General VS Code settings

- **smart_door**
  - **include** - Header files for modular design
  - **lib** - Third-party libraries
  - **src** - Source code
    - `LCD.cpp` - Code for LCD display control
    - `NFC.cpp` - Handles NFC authentication
    - `RGB.cpp` - RGB LED status management
    - `SSensor.cpp` - Sound sensor functionality
    - `main.cpp` - Program entry point
    - `motor.cpp` - Motor operations for locking/unlocking
    - `wifi.cpp` - WiFi functionality and web server
  - **test** - Unit tests for individual components
    - `LCD_testcase.cpp` - Tests for the LCD module
    - `RGB_testcase.cpp` - Tests for the RGB module
    - `SSensor_testcase.cpp` - Tests for the sound sensor
    - `motor_testcase.cpp` - Tests for motor operations
    - `wifi_testcase.cpp` - Tests for WiFi functionality

- **smartdoorweb**
  - **public** - Static files for the web interface
  - **src** - Web application source files

- `.gitignore` - Git ignore file
- `platformio.ini` - PlatformIO configuration

# Project Test Suite

This repository contains a suite of unit tests written using the Unity Test Framework to validate various components of the project. The tests are designed to ensure the correct functionality of modules such as motors, LCD displays, RGB LEDs, and sound sensors.

## Test Modules

### 1. **Motor Tests**
The motor module tests the functionality of the servo motor, particularly for locking and unlocking its position. These tests verify that the motor can be controlled to specific angles as required by the system.

- **test_servo_lock:** Validates that the motor locks correctly at a specific position (0 degrees).
- **test_servo_unlock:** Validates that the motor unlocks and moves to the expected position (90 degrees).

### 2. **LCD Tests**
The LCD module is tested for proper initialization and the ability to display messages and text on the screen. This suite includes tests for clearing rows, saving the display mode, and ensuring correct text output.

- **test_LCD_init:** Verifies the correct initialization of the LCD.
- **test_lcd_show_message:** Tests displaying a custom message on the LCD.
- **test_lcd_clearRow:** Ensures that a row of the LCD can be cleared.
- **test_lcd_showRow:** Verifies that text can be shown on a specified row.
- **test_lcd_savemode:** Tests saving the current display mode of the LCD.

### 3. **RGB LED Tests**
These tests ensure that the RGB LED module can display the correct colors and can be turned off. The suite includes tests for basic colors as well as the ability to turn off the LEDs.

- **test_rgb_red:** Verifies that the red color is displayed correctly on the RGB LED.
- **test_rgb_green:** Verifies that the green color is displayed correctly on the RGB LED.
- **test_rgb_blue:** Verifies that the blue color is displayed correctly on the RGB LED.
- **test_rgb_white:** Ensures that the white color is displayed correctly on the RGB LED.
- **test_rgb_off:** Verifies that the RGB LED turns off properly.

### 4. **Sound Sensor Tests**
The sound sensor module is tested to verify its ability to detect sound signals. These tests ensure that the sensor responds correctly to detected sounds.

- **test_sound_detect_true:** Ensures that the sound sensor detects sound signals as expected.

## Running Tests

The unit tests for each module are organized into separate functions. You can run all tests by calling the relevant test setup functions in the main `setup()` function of your project. This approach allows for modular testing, where individual test cases can be run independently or all at once for comprehensive validation.

Each test function is designed to run once during the setup phase, with no need for a continuous loop in the `loop()` function of the Arduino or embedded system environment.

## Requirements

- **Unity Test Framework**: The tests use the Unity framework for unit testing. For more information about Unity, visit [Unity Test Framework GitHub](https://github.com/ThrowTheSwitch/Unity).
- **Arduino IDE or PlatformIO**: These platforms are used for compiling and uploading the code to the microcontroller.




## PIN diagram

feat: configure pins for motor, LCD, NFC, RGB LED, and sound sensor

- Motor control pin: 7
- LCD communication pins:
  * SCK (clock)
  * SCL (data)
- NFC module pins:
  * RST/Reset: 9
  * SPI SS (SDA): 10
  * SPI MOSI: 11
  * SPI MISO: 12
  * SPI SCK: 13
- RGB LED pins:
  * RED_PIN: 5
  * GREEN_PIN: 3
  * BLUE_PIN: 4
- Sound sensor input pin: A0

Ensures consistent and clear pin mapping for all components.
