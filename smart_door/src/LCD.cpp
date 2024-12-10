#include "main.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;

void LCD_init() {
  lcd.init();
  lcd.backlight();
  lcd.blink();
  // lcd.command(0xc);
  delay(500);
}

void lcd_show_message(const char* message) {
    lcd.clear();
    // Loop through each row
    for (int row = 0; row < LCD_ROWS; row++) {
        lcd.setCursor(0, row); // Set the cursor to the start of the row

        // Print characters for the current row
        for (int col = 0; col < LCD_COLUMNS; col++) {
            int charIndex = row * LCD_COLUMNS + col;
            if (message[charIndex] == '\0') {
                break; // Stop if end of string is reached
            }
            lcd.print(message[charIndex]);
        }
    }
}

void lcd_clearRow(int row) {
  lcd.setCursor(0, row);
  for (int i = 0; i < LCD_COLUMNS; i++) {
    lcd.print(" "); // Clear the row by printing spaces
  }
}

void lcd_showRow(int row, const char* message) {
  lcd_clearRow(row);           // Optional: Clear the row first
  lcd.setCursor(0, row);       // Set cursor to the specified row
  for (int i = 0; i < LCD_COLUMNS; i++) {
    if (message[i] == '\0') {
      break; // Stop if end of string is reached
    }
    lcd.print(message[i]); // Print character-by-character
  }
}

void lcd_savemode(){
  lcd.noBacklight();
  lcd.clear();
}

