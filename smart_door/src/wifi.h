#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <WiFi.h> // Include the Arduino WiFi library

// Function to initialize WiFi
void wifi_setup();

// Function to handle WiFi reconnection
void wifi_reconnect();

// Function to display WiFi status
void wifi_status();

#endif // WIFI_H
