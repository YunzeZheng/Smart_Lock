#include <Arduino.h>
#include <unity.h>
#include "../src/main.h"
#include "../src/SSenor.cpp"


// Test when the sound level is above the threshold (should return true)
void test_sound_detect_true() {
  bool result = Sounddetect();
  TEST_ASSERT_TRUE(result);
}


void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_sound_detect_true);
  UNITY_END();
}

void loop() {
  // No loop is needed for unit tests
}