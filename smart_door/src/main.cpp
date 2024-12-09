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
const unsigned long webseverDelay = 5L * 60 * 1000;
const unsigned long activityDelay = 20000;
unsigned long unlockStartTime = 0;
bool isUnlocking = false;
String userInput = ""; // For storing user input

void setup() {
  Serial.begin(115200);
  servo_setup();
  LCD_init();
  RGB_setup();
  NFC_setup();
  wifi_setup();
  delay(100);

  lcd_show_message("Welcome to smart lock!");
  delay(100);
  delay(2000);
  lcd_show_message("Setting on WiFi");
  lcd_SecondCol("Follow user Manual");
  delay(5000);
}

void unlockSequence() {
  servo_lock(1); // Unlock
  lcd_show_message("Unlocked");
  Color_set(0, 255, 0); // Green for unlocked
  isUnlocking = true;
}


void handlePowerSave() {
  lcd.backlight();
  // lcd_savemode();
  Color_set(256, 0, 0);
  if(dect_card()){
    current_state = WEBSEVER;
    webseverTimer = millis(); // Initialize web server timer
  }
}

void handleActivity() {
  lcd.backlight();

  if (millis() - activityTimer >= activityDelay) {
    current_state = POWER_SAVE;
    return;
  }

  if(dect_card()){
    current_state = WEBSEVER;
    webseverTimer = millis(); // Initialize web server timer
  }
}

void handleWebsever() {
  lcd.backlight();
  if (millis() - webseverTimer >= webseverDelay) {
    current_state = POWER_SAVE;
    return;
  }
  if (compare_password()) {
    unlockSequence();
    unlockStartTime = millis();
    Color_set(0, 255, 0);
    delay(1000);
  }
  if (millis() - unlockStartTime >= 10000){
    servo_lock(0); // Lock
    lcd_show_message("Access Denied");
  }
  ClientOn(); // Interaction with the web server
}

void loop() {
  // handleUnlockDuration(); // Ensure lock relocks after unlock duration

  switch (current_state) {
    case POWER_SAVE:
      if (Sounddetect()) {
        current_state = ACTIVITY;
        activityTimer = millis(); // Start activity timer
      }
      handlePowerSave();
      break;

    case ACTIVITY:
      Color_set(255, 255, 0); // Set to yellow
      handleActivity();
      break;

    case WEBSEVER:
      Color_set(0, 0, 255); // Set to blue
      handleWebsever();
      break;
  }
}
