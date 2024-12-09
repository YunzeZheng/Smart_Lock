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
bool detectNFC();
void writeNFC(MFRC522::MIFARE_Key* key, byte block, byte* data, byte len);
void readNFC(MFRC522::MIFARE_Key* key, byte block, byte* buffer, byte* len);

#endif;