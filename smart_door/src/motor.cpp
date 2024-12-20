#include <Arduino.h>
#include "main.h"

Servo myservo;

int motor_pin = 7;

void servo_setup() {
  myservo.attach(motor_pin);  // Attach the servo motor to the motor_pin
  servo_lock(0);  // Set initial state to 'locked' (0)
}

void servo_lock(int LockVariable) {
  int val;
  if (LockVariable == 1) {
    myservo.write(120);  // Unlock the servo (rotate to 90 degrees)
  } else {
    myservo.write(0);  // Lock the servo (rotate to 0 degrees)
  }
}