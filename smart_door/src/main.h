// Motor
#ifndef SERVO_H
#define SERVO_H

extern int LockVariable;  //global variable

void servo_setup();
void open_or_lock();

#endif

// NFC
#ifndef NFC_H
#define NFC_H

void NFC_setup();
void dectection();

#endif

// Keypad
#ifndef Keypad_H
#define Keypad_H
#include <Arduino.h>

extern String inputString;

void Keypad_setup();
String StringInput();

#endif