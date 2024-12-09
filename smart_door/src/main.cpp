#include <Arduino.h>
#include "main.h"

enum State {
  POWER_SAVE,
  ACTIVITY,
  WIFI_SERVER
};

int pirPin = 2;
bool locker_state = false;
State current_state = POWER_SAVE;
String password = "zyz134926!";
unsigned long activityTimer = 0;
const unsigned long activityDelay = 20000;

void setup() {
  Serial.begin(115200);
  servo_setup();
  LCD_init();
  RGB_setup();
  NFC_setup();
  delay(100);
  
  lcd_show_message("Welcome to smart lock!");
  delay(100);
  lcd_show_message("Setting on WiFi");
  lcd_SecondCol("Follow user Manual");
  wifi_setup();
}

void handlePowerSave(){
  Color_set(0,0,0);
  lcd_savemode();
  Color_set(256,0,0);
}

void handleActivity(){
  lcd.backlight();
  activityTimer = millis();
  String inputString = "";
  if(inputString == password){
    servo_lock(0);
  }else{
    servo_lock(180);
  }
  while(1){
    //
  }
  if (activityTimer >= activityDelay) {
    current_state = POWER_SAVE;
    handlePowerSave();
  }
}

void handleWiFiServer(){
  Color_set(0,0,256);
  ClientOn();
}

void loop() {
  // Modes functions
  switch (current_state) {
    case POWER_SAVE:
      if (Sounddetect() || detectNFC()) {
        current_state = ACTIVITY;
        break;
      }
      handlePowerSave();
      break;
    case ACTIVITY:
      Color_set(0,256,0);
      lcd.backlight();
      handleActivity();
      break;
    case WIFI_SERVER:
      handleWiFiServer();
      break;
  }

}