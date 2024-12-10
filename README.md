Smart Door Project

Introduction

This project is a smart door system that uses NFC or a WiFi-based web interface to lock/unlock the door. The web interface also allows users to change the WiFi name and password securely.

Features

Unlock Options:

NFC Authentication

Web Interface through http://192.168.4.1

RGB LED Indicators:

Red: Power-saving mode

White: Activity mode

Blue: Web server connection

Green: Door unlocked

Future Enhancements:

Camera Module Integration: Real-time monitoring.

Biometric Authentication: Fingerprint unlock.

AI-Based Face Detection: Enhanced security.

Code Structure

The project is organized as follows:

|-- .vscode
|   |-- c_cpp_properties.json      --> C/C++ IntelliSense configuration
|   |-- launch.json                --> Debugging configuration
|   |-- settings.json              --> General VS Code settings
|
|-- smart_door
|   |-- include                    --> Header files for modular design
|   |
|   |-- lib                        --> Third-party libraries (if any)
|   |
|   |-- src                        --> Source code
|   |   |-- LCD.cpp                --> Code for controlling the LCD display
|   |   |-- NFC.cpp                --> Handles NFC authentication
|   |   |-- RGB.cpp                --> Manages the RGB LED for status indication
|   |   |-- SSensor.cpp            --> Code for the sound sensor
|   |   |-- main.cpp               --> Entry point for the program
|   |   |-- motor.cpp              --> Handles motor operations for locking/unlocking
|   |   |-- wifi.cpp               --> Implements WiFi functionality (e.g., hosting the web server)
|   |
|   |-- test                       --> Component-specific test scripts
|       |-- LCD_testcase.cpp       --> Unit test for the LCD module
|       |-- RGB_testcase.cpp       --> Unit test for the RGB module
|       |-- SSensor_testcase.cpp   --> Unit test for the sound sensor
|       |-- motor_testcase.cpp     --> Unit test for the motor operations
|       |-- wifi_testcase.cpp      --> Unit test for the WiFi functionality
|
|-- smartdoorweb
|   |-- public                     --> Static files for the web interface
|   |-- src                        --> Web application source files
|
|-- .gitignore                     --> Files and folders to ignore in Git
|-- platformio.ini                 --> PlatformIO configuration file

Setup Instructions

Hardware Assembly:

Assemble the circuit as per the final design diagram.

Connect the motor, NFC module, RGB LED, sound sensor, and other components.

Software Setup:

Install PlatformIO in VS Code.

Open the smart_door project folder.

Flash the microcontroller using the platformio.ini configuration.

Deploy the web interface by navigating to smartdoorweb and running the necessary commands to host the page.

Usage Instructions

Unlock the Door:

Tap the registered NFC card.

Or, after connect wifi, log in to the web interface via http://192.168.4.1 and press "Unlock."

Change WiFi Settings:

Navigate to the web interface.

Modify the WiFi name or password under the settings section.

Challenges and Solutions

Challenge 1: Limited power consumption during idle states.

Solution: Implemented a power-saving mode indicated by the red LED.

Challenge 2: Secure web access for WiFi settings.

Solution: Restricted access to authorized users via NFC and password protection.

Future Features

Camera Module Integration: Real-time image capture for monitoring.

Biometric Authentication: Fingerprint unlock for added security.

AI Face Detection: Recognize faces for seamless entry.

Project Test Suite

This repository contains a suite of unit tests written using the Unity Test Framework to validate various components of the project. The tests ensure the correct functionality of modules such as motors, LCD displays, RGB LEDs, and sound sensors.

Test Modules

1. Motor Tests:

test_servo_lock: Validates that the motor locks correctly at a specific position (0 degrees).

test_servo_unlock: Validates that the motor unlocks and moves to the expected position (90 degrees).

2. LCD Tests:

test_LCD_init: Verifies the correct initialization of the LCD.

test_lcd_show_message: Tests displaying a custom message on the LCD.

test_lcd_clearRow: Ensures that a row of the LCD can be cleared.

test_lcd_showRow: Verifies that text can be shown on a specified row.

test_lcd_savemode: Tests saving the current display mode of the LCD.

3. RGB LED Tests:

test_rgb_red: Verifies that the red color is displayed correctly on the RGB LED.

test_rgb_green: Verifies that the green color is displayed correctly on the RGB LED.

test_rgb_blue: Verifies that the blue color is displayed correctly on the RGB LED.

test_rgb_white: Ensures that the white color is displayed correctly on the RGB LED.

test_rgb_off: Verifies that the RGB LED turns off properly.

4. Sound Sensor Tests:

test_sound_detect_true: Ensures that the sound sensor detects sound signals as expected.

Running Tests:

Run all tests by calling the relevant test setup functions in the setup() function of your project. Individual test cases can also be run independently.

PIN diagram
feat: configure pins for motor, LCD, NFC, RGB LED, and sound sensor

Motor control pin: 7
LCD communication pins:
SCK (clock)
SCL (data)
NFC module pins:
RST/Reset: 9
SPI SS (SDA): 10
SPI MOSI: 11
SPI MISO: 12
SPI SCK: 13
RGB LED pins:
RED_PIN: 5
GREEN_PIN: 3
BLUE_PIN: 4
Sound sensor input pin: A0
Ensures consistent and clear pin mapping for all components.