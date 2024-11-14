#include <SPI.h>
#include <MFRC522.h>
#include "main.h"

// Define the pins for the RC522 module
#define SS_PIN 10   // Pin connected to SDA of RC522
#define RST_PIN 9   // Pin connected to RST of RC522

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create an MFRC522 instance

void NFC_setup() {
  Serial.begin(115200);
  	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme

}

void dectection() {
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  open_or_lock(1);
  delay(2000);
}

void writePassword(const String& password) {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    MFRC522::StatusCode status;
    byte block = 4;
    byte buffer[16];
    memset(buffer, 0, sizeof(buffer));
    strncpy((char*)buffer, password.c_str(), sizeof(buffer));

    status = mfrc522.MIFARE_Write(block, buffer, 16);
    if (status == MFRC522::STATUS_OK) {
      Serial.println("Password written successfully!");
    } else {
      Serial.print("Write failed: ");
      Serial.println(mfrc522.GetStatusCodeName(status));
    }
    mfrc522.PICC_HaltA();
  }
}

void readPassword() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    MFRC522::StatusCode status;
    byte block = 4;
    byte buffer[18];
    byte size = sizeof(buffer);

    status = mfrc522.MIFARE_Read(block, buffer, &size);
    if (status == MFRC522::STATUS_OK) {
      Serial.print("Password read: ");
      for (byte i = 0; i < 16; i++) {
        Serial.write(buffer[i]);
      }
      Serial.println();
    } else {
      Serial.print("Read failed: ");
      Serial.println(mfrc522.GetStatusCodeName(status));
    }
    mfrc522.PICC_HaltA();
  }
}
