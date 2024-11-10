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
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void dectection() {
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
