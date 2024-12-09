#ifndef NFC_H
#define NFC_H
#include "nfc.h"
#include <Arduino.h>

// Function to initialize NFC
void NFC_setup();

// Function to read NFC tag
String NFC_readTag();

// Function to write NFC tag
void NFC_writeTag(const String& data);

#endif // NFC_H
