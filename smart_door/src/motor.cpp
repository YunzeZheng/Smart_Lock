#include <Servo.h>
#include "main.h"

Servo myservo;

int motor_pin = 7;

void servo_setup() {
  myservo.attach(motor_pin);  // Attach the servo motor to the motor_pin
  open_or_lock(0);  // Set initial state to 'locked' (0)
}

void open_or_lock(int LockVariable) {
  int val;
  if (LockVariable == 1) {  // Use '==' to compare values
    myservo.write(180);  // Unlock the servo (rotate to 180 degrees)
  } else {
    myservo.write(0);  // Lock the servo (rotate to 0 degrees)
  }
  delay(1000);
}