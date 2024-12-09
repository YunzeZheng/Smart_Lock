#ifndef MAIN_H
#define MAIN_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiS3.h>
#include <Servo.h>
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
extern char* valueToWrite;
extern char* DEFAULT_SSID;
extern char* DEFAULT_PASSWORD;

// --- Sound Senor Control ---
extern int timer;
bool Sounddetect();

// --- RGB Control ---
extern int RED_PIN;
extern int GREEN_PIN;
extern int BLUE_PIN;
void RGB_setup();
void Color_set(int redValue, int greenValue, int blueValue);

// --- Motor Control ---
void servo_setup();
void servo_lock(int LockVariable);

// --- LCD Control ---
extern LiquidCrystal_I2C lcd;
void LCD_init();
void lcd_show_message(const char* message);
void lcd_FirstCol(const char* message);
void lcd_SecondCol(const char* message);
void lcd_savemode();

// --- Wi-Fi Setup ---
extern bool locker_state;
void wifi_setup();
void ClientOn();

// --- NFC Setup ---
extern MFRC522 mfrc522;
void NFC_setup();
bool compare_password();
void writeDataToBlock(byte block, const char* data);
String readDataFromBlock(byte block);

#endif;