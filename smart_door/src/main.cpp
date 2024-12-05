#include <Arduino.h>
#include "main.h"

int pirPin = 2;
const char init_ssid[] = "smart_door";  // Defined SSID
const char init_password[] = "66666666";  // Defined Password

void setup() {
  Serial.begin(115200);
  delay(5000);
  servo_setup();
  LCD_init();
  delay(100);
  
  lcd_show_message("Welcome to smart lock!");
  delay(100);

  lcd_show_message("Setting on WIFI");
  lcd_SecondCol("Follow user Manual");
  wifi_setup(init_ssid, init_password);

  delay(2000);
  handleClient();
  delay(5000);
  lcd_FirstCol("Done");
}

void loop() {
  // delay(1000);
  // dectection();
  // open_or_lock(0);
}