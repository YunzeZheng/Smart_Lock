#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>

// Enums
enum State {
  POWER_SAVE,
  ACTIVITY
};

// Global variables
extern int pirPin;
extern bool locker_state;
extern State current_state;
extern String password;
extern unsigned long activityTimer;
extern const unsigned long activityDelay;

// Function prototypes
void servo_setup();
void LCD_init();
void RGB_setup();
void NFC_setup();
void wifi_setup();
void lcd_show_message(const String& message);
void lcd_SecondCol(const String& message);
void lcd_savemode();
void Color_set(int r, int g, int b);
bool Sounddetect();
void servo_lock(int state);
void handlePowerSave();
void handleActivity();

#endif // MAIN_H
