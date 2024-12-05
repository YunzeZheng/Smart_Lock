#ifndef MAIN_H
#define MAIN_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiS3.h>
#include <Servo.h>
#include <Arduino.h>

// --- Motor Control ---
extern int testvalue;
void servo_setup();
void open_or_lock(int);

// --- LCD Control ---
extern LiquidCrystal_I2C lcd;
void LCD_init();
void lcd_show_message(const char* message);
void lcd_FirstCol(const char* message);
void lcd_SecondCol(const char* message);

// --- Wi-Fi Setup ---
extern const char init_ssid[];
extern const char init_password[];
extern WiFiServer server;
extern String inputPassword;
void wifi_setup(const char* Set_ssid, const char* Set_password);
void handleClient();

// --- NFC Setup ---

#endif