#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

const char *valueToWrite = "RFIDTest123456";  // Example value to write to the card

void setup() {
  Serial.begin(115200);             // Initialize serial communications with the PC
  SPI.begin();                    // Initialize SPI bus
  mfrc522.PCD_Init();             // Initialize MFRC522 card
  Serial.println(F("Ready to read and write RFID card"));
}

void loop() {
  // Prepare key - default key is FFFFFFFFFFFFh
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

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
  // Perform write operation
  writeDataToBlock(4, valueToWrite);

  //-------------------------------------------
  // Perform read operation
  String readValue = readDataFromBlock(4);

  //-------------------------------------------
  // Compare the read value with the expected value
  if (readValue == valueToWrite) {
    Serial.println(F("The read value matches the expected value!"));
  } else {
    Serial.println(F("The read value does not match the expected value."));
  }

  //-------------------------------------------
  Serial.println(F("\n**End Reading and Writing**\n"));

  delay(1000); // Adjust this delay as needed

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

// Function to write data to a specified block
void writeDataToBlock(byte block, const char* data) {
  byte buffer[18];
  byte len = 16; // Length of the data
  for (byte i = 0; i < len; i++) {
    buffer[i] = data[i]; // Copy data into buffer
  }

  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;  // Default key

  MFRC522::StatusCode status;

  // Authenticate and write data to the block
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Write(block, buffer, len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Writing failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  Serial.println(F("Data written to block"));
}

// Function to read data from a specified block
String readDataFromBlock(byte block) {
  byte buffer[18];
  byte len = 18; // Length of the buffer

  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;  // Default key

  MFRC522::StatusCode status;

  // Authenticate and read data from the block
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return "";
  }

  status = mfrc522.MIFARE_Read(block, buffer, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return "";
  }

  // Convert the read data to a string
  String readValue = "";
  for (uint8_t i = 0; i < 16; i++) {
    if (buffer[i] != 32) {  // Exclude padding spaces
      readValue += (char)buffer[i];
    }
  }

  return readValue;
}
