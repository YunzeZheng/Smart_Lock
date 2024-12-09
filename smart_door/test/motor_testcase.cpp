#include <Arduino.h>
#include <unity.h>
#include "../src/main.h"
#include "../src/motor.cpp"

void setUp() {
  myservo.attach(motor_pin);
}

// Test case for locking the servo (0 degrees)
void test_servo_lock() {
  servo_lock(0);
  delay(2000);
  TEST_ASSERT_EQUAL(0, myservo.read());
}

// Test case for unlocking the servo (90 degrees)
void test_servo_unlock() {
  servo_lock(1);
  delay(2000);
  TEST_ASSERT_EQUAL(119, myservo.read());
}

void setup2() {
  UNITY_BEGIN();
  RUN_TEST(test_servo_lock);
  RUN_TEST(test_servo_unlock);
  UNITY_END();
}

void loop2() {
  // No need for a loop in unit tests
}
