#include <Arduino.h>
#include <unity.h>
#include "../src/main.h"
#include "../src/wifi.cpp"

void setup() {
	Serial.begin(115200);
    wifi_setup();
}

void loop() {
	ClientOn();
}