#include <Arduino.h>
#include "../src/main.h"
#include "../src/LCD.cpp"

// Custom test result function
void log_test_result(const char* test_name, bool result) {
    Serial.print("[TEST] ");
    Serial.print(test_name);
    Serial.println(result ? " PASSED" : " FAILED");
}

// Test cases
void test_lcd_initialization() {
    Serial.println("Running test_lcd_initialization...");
    LCD_init(); // Initialize the LCD
    lcd_show_message("Init Test");
}

void test_lcd_show_message() {
    Serial.println("Running test_lcd_show_message...");
    const char* test_message = "Hello, World! Hope You Have Fun";
    lcd_show_message(test_message);
    log_test_result("LCD Show Message", true); // Assume manual check
}

void setup1() {
    Serial.begin(115200);
    delay(1000); // Give time for the serial monitor to connect

    Serial.println("Starting LCD tests...");
    test_lcd_initialization();
    delay(2000); // Pause to observe the LCD
    test_lcd_show_message();
    delay(2000); // Pause to observe the LCD
    Serial.println("All tests completed.");
}

void loop1() {
    // No loop actions needed for testing
}