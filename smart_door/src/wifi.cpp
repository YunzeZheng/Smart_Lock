#include <WiFiS3.h>

void wifi_connection() {
  // start
  Serial.println("Scanning for available networks...");
  int numNetworks = WiFi.scanNetworks();
  // print the network name
  if (numNetworks == 0) {
    Serial.println("No networks found.");
    return;
  } else {
    Serial.println("Networks found:");
    for (int i = 0; i < numNetworks; i++) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(WiFi.SSID(i));
    }
  }
  // wifi name
  Serial.println("Enter the number of the network you want to connect to:");
  while (Serial.available() == 0) {
    // Wait
  }
  int networkIndex = Serial.parseInt() - 1;  // Convert to zero-based index
  // clear
  while (Serial.available()) {
    Serial.read();
  }
  // password
  String password;
  Serial.println("Enter the password for the selected network:");
  while (Serial.available() == 0) {
    // wait
  }
  password = Serial.readStringUntil('\n');

  // Connect
  Serial.print("Connecting to ");
  Serial.println(WiFi.SSID(networkIndex));
  WiFi.begin(WiFi.SSID(networkIndex), password.c_str());
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi!");
}