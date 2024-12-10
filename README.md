Smart Door Project
Introduction
This project is a smart door system that uses NFC authentication or a WiFi-based web interface to lock/unlock the door. The web interface also allows users to securely change the WiFi name and password.

Features
Unlock Options:
NFC Authentication
Web Interface: Accessible at http://192.168.4.1
RGB LED Indicators:
Red: Power-saving mode
White: Activity mode
Blue: Web server connection
Green: Door unlocked
Future Enhancements:
Integration of a camera module for real-time monitoring.
Biometric authentication (e.g., fingerprint).
AI-based face detection for enhanced security.
Code Structure
The project is organized as follows:

sql
Copy code
|-- .vscode
|   |-- c_cpp_properties.json      --> C/C++ IntelliSense configuration
|   |-- launch.json                --> Debugging configuration
|   |-- settings.json              --> General VS Code settings
|
|-- smart_door
|   |-- include                    --> Header files for modular design
|   |-- lib                        --> Third-party libraries (if any)
|   |-- src                        --> Source code
|   |   |-- LCD.cpp                --> Code for LCD display control
|   |   |-- NFC.cpp                --> Handles NFC authentication
|   |   |-- RGB.cpp                --> RGB LED status management
|   |   |-- SSensor.cpp            --> Sound sensor functionality
|   |   |-- main.cpp               --> Program entry point
|   |   |-- motor.cpp              --> Motor operations for locking/unlocking
|   |   |-- wifi.cpp               --> WiFi functionality and web server
|   |-- test                       --> Unit tests for individual components
|       |-- LCD_testcase.cpp       --> Tests for the LCD module
|       |-- RGB_testcase.cpp       --> Tests for the RGB module
|       |-- SSensor_testcase.cpp   --> Tests for the sound sensor
|       |-- motor_testcase.cpp     --> Tests for motor operations
|       |-- wifi_testcase.cpp      --> Tests for WiFi functionality
|
|-- smartdoorweb
|   |-- public                     --> Static files for the web interface
|   |-- src                        --> Web application source files
|
|-- .gitignore                     --> Git ignore file
|-- platformio.ini                 --> PlatformIO configuration
Setup Instructions
Hardware Assembly:
Assemble the circuit as per the final design diagram.
Connect the motor, NFC module, RGB LED, sound sensor, and other components.
Software Setup:
Install PlatformIO in VS Code.
Open the smart_door project folder.
Flash the microcontroller using the platformio.ini configuration.
Deploy the web interface:
Navigate to the smartdoorweb folder.
Run necessary commands to host the web page.
Usage Instructions
Unlock the Door:
Tap a registered NFC card.
Or log in to the web interface via http://192.168.4.1 and press "Unlock."
Change WiFi Settings:
Use the web interface to modify WiFi credentials in the settings section.

Challenges and Solutions
NFC Storage Format:

Challenge: The NFC module used a unique storage format, differing from the standard matrix format, causing confusion in data handling.
Solution: Spent time analyzing the module's documentation and developed a custom handler to process the NFC data correctly.
LCD Display Connections:

Challenge: Limited board space and multiple ports complicated the integration of the LCD display.
Solution: Optimized the circuit layout and used a smaller breadboard with jumper wires to ensure proper connections.
Servo Motor Constraints:

Challenge: The 180-degree range of the servo motor initially seemed restrictive for the locking mechanism.
Solution: After reassessing, determined that a simple open/close functionality was sufficient. Retained the servo motor and simplified the locking logic to match its capabilities.

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
