#ifndef MAIN_H
#define MAIN_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiS3.h>
#include <Servo.h>
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
extern String password;
extern char* valueToWrite;
extern const int MAX_SSID_LENGTH;
extern const int MAX_PASS_LENGTH;
extern char current_ssid[];
extern char current_password[];

// -- main --
extern void unlockSequence();

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
extern unsigned long unlockStartTime;
void servo_setup();
void servo_lock(int LockVariable);

// --- LCD Control ---
extern LiquidCrystal_I2C lcd;
void LCD_init();
void lcd_show_message(const char* message);
void lcd_clearRow(int row);
void lcd_showRow(int row, const char* message);
void lcd_savemode();

// --- Wi-Fi Setup ---
extern WiFiServer server;
void wifi_setup();
void ClientOn();
void wifi_end();

// --- NFC Setup ---
extern char* valueToWrite;
extern MFRC522 mfrc522;
void NFC_setup();
bool compare_password();
void writeDataToBlock(byte block, const char* data);
String readDataFromBlock(byte block);
bool dect_card();

#endif;