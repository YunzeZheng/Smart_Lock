#include "main.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void LCD_init() {
  lcd.init();
  lcd.backlight();
  lcd.blink();
  // lcd.command(0xc);
  delay(500);
}

void lcd_show_message(const char* message) {
    lcd.clear();
    lcd.setCursor(0, 0);
    for (int i = 0; i < 16; i++) {
      if (message[i] == '\0'){
          break;
        }else{
          lcd.print(message[i]);
      }
    }
    lcd.setCursor(0, 1);  // Move to the second row
    for (int i = 16; i < 32; i++) {
      if (message[i] == '\0'){
        break;
      }else{
        lcd.print(message[i]);
      }
    }
}

void lcd_FirstCol(const char* message) {
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void lcd_SecondCol(const char* message) {
  lcd.setCursor(0, 1); 
  lcd.print(message);
}

void lcd_savemode(){
  lcd.noBacklight();
  lcd.clear();
}

