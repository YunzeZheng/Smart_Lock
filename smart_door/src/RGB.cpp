#include <Arduino.h>
#include "main.h"
// Define the PWM pins for RGB LED
const int redPin = 16;
const int greenPin = 17;
const int bluePin = 18;

void RGB_setup() {
  // Set the RGB pins as output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void Color_set(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
