#include <Arduino.h>
#include "main.h"

enum State {
  POWER_SAVE,
  ACTIVITY,
  WEBSEVER
};

int pirPin = 2;
bool locker_state = false;
State current_state = POWER_SAVE;
unsigned long activityTimer = 0;
unsigned long webseverTimer = 0;
unsigned long unlockStartTime = 0;
unsigned long ClientTimer = 0;

const unsigned long webseverDelay = 2L * 60 * 1000; // 5 minutes
const unsigned long activityDelay = 20000;         // 20 seconds
const unsigned long unlockDuration = 10000;        // 10 seconds
const unsigned long clientWaitDelay = 20000;       // 20 seconds

bool isUnlocking = false;
bool clientDetected = false;
uint8_t RGB_color[] = {0, 0, 0};

void setup() {
  Serial.begin(115200);
  servo_setup();
  LCD_init();
  RGB_setup();
  NFC_setup();
  wifi_setup();
  delay(100);

  lcd_show_message("Welcome to smart lock!");
  delay(2000);
  lcd_show_message("Setting up WiFi");
  lcd_SecondCol("Follow user Manual");
  delay(5000);
}

void unlockSequence() {
  servo_lock(1); // Unlock
  lcd_show_message("Unlocked");
  Color_set(0, 255, 0); // Green for unlocked
  isUnlocking = true;
  unlockStartTime = millis();
  ClientTimer = millis(); // Start client wait timer
  clientDetected = true;  // Flag indicating a user interaction
}

void checkLockTimeout() {
  if (isUnlocking && (millis() - unlockStartTime >= unlockDuration)) {
    servo_lock(0); // Lock
    lcd_show_message("Locked");
    isUnlocking = false;
  }
}

void handlePowerSave() {
  lcd_savemode();
  if (isUnlocking){
    Color_set(0, 255, 0); // Green for unlocked
  }else{
    Color_set(255, 0, 0); //
  }

  if (Sounddetect()) {
    Serial.println("Sound detected, switching to ACTIVITY.");
    current_state = ACTIVITY;
    activityTimer = millis(); // Start activity timer
  }

  if (server.available()) {
    Serial.println("Client connected, switching to WEBSEVER.");
    current_state = WEBSEVER;
    return;
  }

  if (compare_password()) {
    unlockSequence();
  }
}

void handleActivity() {
  lcd.backlight();
  if (isUnlocking){
    Color_set(0, 255, 0); // Green for unlocked
  }else{
    Color_set(255, 255, 255); // White for activity mode
  }

  if (millis() - activityTimer >= activityDelay) {
    Serial.println("Activity timeout, switching to POWER_SAVE.");
    current_state = POWER_SAVE;
    return;
  }

  if (server.available()) {
    Serial.println("Client connected, switching to WEBSEVER.");
    current_state = WEBSEVER;
    webseverTimer = millis();
    return;
  }

  if (compare_password()) {
    unlockSequence();
  }

  if (clientDetected && (millis() - ClientTimer >= clientWaitDelay)) {
    Serial.println("Client wait timeout, switching to WEBSEVER.");
    current_state = WEBSEVER;
    clientDetected = false;   // Reset the client detected flag
  }

  checkLockTimeout();
}

void handleWebsever() {
  lcd.backlight();
  if (isUnlocking){
    Color_set(0, 255, 0); // Green for unlocked
  }else{
    Color_set(0, 0, 255); // Blue for web server mode
  }

  if (millis() - webseverTimer >= webseverDelay) {
    Serial.println("Webserver timeout, switching to POWER_SAVE.");
    current_state = POWER_SAVE;
    return;
  }

  ClientOn(); // Interaction with the web server
}

void loop() {
  checkLockTimeout(); // Ensure lock relocks after unlock duration

  switch (current_state) {
    case POWER_SAVE:
      handlePowerSave();
      break;

    case ACTIVITY:
      handleActivity();
      break;

    case WEBSEVER:
      handleWebsever();
      break;
  }
}
