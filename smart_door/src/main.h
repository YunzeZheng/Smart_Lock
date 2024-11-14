#include <Arduino.h>

// Motor
#ifndef SERVO_H
#define SERVO_H

void servo_setup();
void open_or_lock(int);

#endif

// Keypad
#ifndef Keypad_H
#define Keypad_H

void Keypad_setup();
String StringInput();

#endif

// Keypad
#ifndef LCD_H
#define LCD_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;
    
void LCD_init();               // Function to initialize the LCD
void lcd_show_message(const char* message); // Function to show a message on the LCD

#endif


// Keypad
#ifndef WIFI_H
#define WIFI_H
    
void wifi_connection();

#endif

#ifndef NFC_H
#define NFC_H

#include <Arduino.h>

void NFC_setup();
void dectection();
void writePassword(const String& password);
void readPassword();

#endif
