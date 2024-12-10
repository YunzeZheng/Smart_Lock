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

const unsigned long webseverDelay = 2L * 60 * 1000; // 2 minutes
const unsigned long activityDelay = 30000;         // 30 seconds
const unsigned long unlockDuration = 10000;        // 10 seconds

bool isUnlocking = false;
State previous_state = POWER_SAVE;

bool activityFirstEntry = true; // Tracks first entry into ACTIVITY
bool webserverFirstEntry = true; // Tracks first entry into WEBSEVER

void lcd_oneTimeMessage(const char* row0, const char* row1) {
    lcd_clearRow(0);
    lcd_clearRow(1);
    lcd_showRow(0, row0);
    lcd_showRow(1, row1);
}

void setup() {
  Serial.begin(115200);
  servo_setup();
  LCD_init();
  RGB_setup();
  NFC_setup();
  // wifi_setup();
  delay(100);

  lcd_show_message("Welcome to smart lock!");
  delay(2000);
  lcd_oneTimeMessage("Setting up WiFi","Follow user Manual");
  delay(5000);
  lcd_clearRow(0);
  lcd_clearRow(1);
}

void unlockSequence() {
  servo_lock(1); // Unlock
  lcd_oneTimeMessage("Unlocked","");
  Color_set(0, 255, 0); // Green for unlocked
  delay(1000);
  isUnlocking = true;
  unlockStartTime = millis();
}

void checkLockTimeout() {
  if (isUnlocking && (millis() - unlockStartTime >= unlockDuration)) {
    servo_lock(0); // Lock
    lcd_oneTimeMessage("Locked","");
    isUnlocking = false;
  }
}

void handlePowerSave() {
  lcd_savemode();
  wifi_end();

  if (isUnlocking){
    Color_set(0, 255, 0); // Green for unlocked
  }else{
    Color_set(255, 0, 0); //
  }

  if (Sounddetect()) {
    current_state = ACTIVITY;
    activityTimer = millis(); // Start activity timer
  }

  if (compare_password()) {
    unlockSequence();
  }

}

void handleActivity() {
  if (activityFirstEntry) {
    wifi_setup(); // Turn on WiFi
    lcd.backlight();
    lcd_show_message("Please tap your card");
    activityFirstEntry = false; // Reset flag after first entry
  }

  if (isUnlocking){
    Color_set(0, 255, 0); // Green for unlocked
  }else{
    Color_set(255, 255, 255); // White for activity mode
  }

  if (millis() - activityTimer >= activityDelay) {
    current_state = POWER_SAVE;
    return;
  }

  if (server.available()) {
    current_state = WEBSEVER;
    webseverTimer = millis();
    return;
  }

  if (compare_password()) {
    unlockSequence();
  }
}

void handleWebsever() {
  // Display a one-time message when entering Activity Mode
  static bool webserverFirstEntry = true; // If needed locally instead of globally

  if (webserverFirstEntry) {
    lcd.backlight();
    lcd_clearRow(0);
    lcd_clearRow(1);
    lcd_oneTimeMessage("Web Control On", current_ssid);
      webserverFirstEntry = false; // Reset flag after first entry
  }

  if (isUnlocking){
    Color_set(0, 255, 0); // Green for unlocked
  }else{
    Color_set(0, 0, 255); // Blue for web server mode
  }

  if (millis() - webseverTimer >= webseverDelay) {
    if(server.available()){
      return;
    }else{
      current_state = POWER_SAVE;
    }
    return;
  }

  ClientOn(); // Interaction with the web server
}

void loop() {
  checkLockTimeout(); // Ensure lock relocks after unlock duration

  // Check for state transition
  if (current_state != previous_state) {
      if (current_state == ACTIVITY) {
        activityFirstEntry = true; // Reset flag for Activity Mode
      } else if (current_state == WEBSEVER) {
        webserverFirstEntry = true; // Reset flag for Webserver Mode
      }
      previous_state = current_state; // Update the previous state
  }

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


