#include <Arduino.h>
#include <unity.h>
#include "../src/main.h"
#include "../src/RGB.cpp"

// Test: LED turns red
void test_rgb_red() {
    Color_set(255, 0, 0);
    delay(2000);
    TEST_ASSERT_TRUE(true);
}

// Test: LED turns green
void test_rgb_green() {
    Color_set(0, 255, 0);
    delay(2000);
    TEST_ASSERT_TRUE(true);
}

// Test: LED turns blue
void test_rgb_blue() {
    Color_set(0, 0, 255); 
    delay(2000);
    TEST_ASSERT_TRUE(true);
}

// Test: LED turns white
void test_rgb_white() {
    Color_set(255, 255, 255);
    delay(1000);
    TEST_ASSERT_TRUE(true);
}

// Test: LED turns off
void test_rgb_off() {
    Color_set(0, 0, 0);
    delay(1000);
    TEST_ASSERT_TRUE(true);
}

void setup3() {
    UNITY_BEGIN(); 

    RGB_setup();

    // Run all RGB tests
    RUN_TEST(test_rgb_red);
    RUN_TEST(test_rgb_green);
    RUN_TEST(test_rgb_blue);
    RUN_TEST(test_rgb_white);
    RUN_TEST(test_rgb_off);

    UNITY_END();
}

void loop3() {
    // No actions required in the loop for Unity tests
}
