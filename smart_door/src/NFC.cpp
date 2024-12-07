#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

void setup() {
  Serial.begin(9600);             // Initialize serial communications with the PC
  SPI.begin();                    // Initialize SPI bus
  mfrc522.PCD_Init();             // Initialize MFRC522 card
  Serial.println(F("Ready to read and write RFID card"));
}

void loop() {
  // Prepare key - default key is FFFFFFFFFFFFh
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------
  // Check if a new card is present on the sensor/reader
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select the card
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("**Card Detected:**"));
  
  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); // Dump UID details to Serial Monitor

  //-------------------------------------------
  // Write data to block 4 (for example)
  byte buffer1[18] = {'A', 'l', 'i', 'c', 'e', ' ', 'S', 'm', 'i', 't', 'h', ' ', '1', '2', '3', '4'};  // Example data
  block = 4;  // Block to write data to
  len = 16;   // Length of the data

  // Authenticate and write data to block 4
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Write(block, buffer1, len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Writing failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  Serial.println(F("Data written to block 4"));

  //-------------------------------------------
  // Read data from block 4
  byte buffer2[18];
  block = 4;  // Block to read from
  len = 182;   // Length of the buffer

  // Authenticate and read data from block 4
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // Print the data read from block 4
  Serial.print(F("Data in block 4: "));
  for (uint8_t i = 0; i < 16; i++) {
    if (buffer2[i] != 32) {  // Exclude padding spaces
      Serial.write(buffer2[i]);
    }
  }
  Serial.println();

  //-------------------------------------------
  Serial.println(F("\n**End Reading and Writing**\n"));

  delay(1000); // Adjust this delay as needed

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}