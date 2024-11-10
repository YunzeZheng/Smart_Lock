#include <Servo.h>
#include "main.h"

Servo myservo;

int motor_pin = 9;

void servo_setup() {
  myservo.attach(motor_pin);
}

void open_or_lock() {
  int val;
  if(LockVariable = 1){
    myservo.write(180);
  }else{
    myservo.write(0);
  }
}