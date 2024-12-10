#include "main.h"
#include <Arduino.h>

const int soundSensorPin = A0;

int soundLevel = 0;

bool Sounddetect() {
  soundLevel = analogRead(soundSensorPin);
   Serial.println(soundLevel);
  if (soundLevel < 2000 &&soundLevel > 80) {
    return true;
  } else {
    return false;
  }
  delay(4);
}
