#include "main.h"

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

void NFC_setup() {
  SPI.begin();                    // Initialize SPI bus
  mfrc522.PCD_Init();             // Initialize MFRC522 card
  Serial.println(F("Ready to read and write RFID card"));
}

bool detectNFC() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return false;
  }

  Serial.println(F("**Card Detected:**"));
  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); // Dump UID details to Serial Monitor
  return true;
}

void writeNFC(MFRC522::MIFARE_Key* key, byte block, byte* data, byte len) {
  MFRC522::StatusCode status;

  // Authenticate
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }

  // Write data
  status = mfrc522.MIFARE_Write(block, data, len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Writing failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }

  Serial.println(F("Data written successfully."));
}

void readNFC(MFRC522::MIFARE_Key* key, byte block, byte* buffer, byte* len) {
  MFRC522::StatusCode status;

  // Authenticate
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }

  // Read data
  status = mfrc522.MIFARE_Read(block, buffer, len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }

  Serial.print(F("Data in block "));
  Serial.print(block);
  Serial.print(F(": "));
  for (uint8_t i = 0; i < 16; i++) {
    if (buffer[i] != 32) {  // Exclude padding spaces
      Serial.write(buffer[i]);
    }
  }
  Serial.println();
}
