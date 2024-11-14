#include "main.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void LCD_init() {
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.blink();
  delay(500);
}

void lcd_show_message(const char* message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}