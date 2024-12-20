#include <Arduino.h>
#include "main.h"

int RED_PIN = 5;
int GREEN_PIN = 3;
int BLUE_PIN = 4;

void RGB_setup() {
  // Set the RGB pins as output
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode( BLUE_PIN, OUTPUT);
}

void Color_set(int redValue, int greenValue, int blueValue) {
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);
}
