#include <Arduino.h>
#include "main.h"

int pirPin = 2;
String password = "";

void setup() {
  Serial.begin(115200);
  servo_setup();
  LCD_init();
  NFC_setup();
  delay(3000);
  

  lcd_show_message("1-wifi 2-offline");
  delay(1000);

  // Keypad_setup();
  // String password = StringInput();

  while (Serial.available() == 0) {
    // Do nothing
  }
  String inputString = Serial.readString();  
  inputString.trim();
  if (inputString == "1") {
    lcd_show_message("WIFI on");
    wifi_connection();
  } else {
    lcd_show_message("offline on");
    lcd_show_message("set new password");

    while (Serial.available() == 0) {
      // Waiting for user to input the password
    }
    password = Serial.readString();
    Serial.println(password);
    lcd_show_message("Writing to NFC...");
    writePassword(password);
  }
  lcd_show_message("Setup Complete");
}


void loop() {
  delay(1000);
  dectection();
  open_or_lock(0);
}