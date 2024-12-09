#include <Arduino.h>
#include <unity.h>
#include "../src/main.h"
#include "../src/RGB.cpp"

// Test: LED turns red
void test_rgb_red() {
    Color_set(255, 0, 0); // Red
    delay(500);              // Observation time
    TEST_ASSERT_TRUE(true);  // Placeholder for visual confirmation
}

// Test: LED turns green
void test_rgb_green() {
    Color_set(0, 255, 0); // Green
    delay(500);
    TEST_ASSERT_TRUE(true);
}

// Test: LED turns blue
void test_rgb_blue() {
    Color_set(0, 0, 255); // Blue
    delay(500);
    TEST_ASSERT_TRUE(true);
}

// Test: LED turns white
void test_rgb_white() {
    Color_set(255, 255, 255); // White
    delay(500);
    TEST_ASSERT_TRUE(true);
}

// Test: LED turns off
void test_rgb_off() {
    Color_set(0, 0, 0); // Off
    delay(500);
    TEST_ASSERT_TRUE(true);
}

void setup() {
    // Initialize Unity Test Framework
    UNITY_BEGIN();

    // Initialize RGB LED pins
    RGB_setup();

    // Run tests
    RUN_TEST(test_rgb_red);
    RUN_TEST(test_rgb_green);
    RUN_TEST(test_rgb_blue);
    RUN_TEST(test_rgb_white);
    RUN_TEST(test_rgb_off);

    // End testing
    UNITY_END();
}

void loop() {
    // No actions required in loop for Unity tests
}
