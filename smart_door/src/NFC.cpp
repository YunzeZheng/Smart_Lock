#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above
#define DOOR_PIN        8           // Pin connected to door lock mechanism
#define OPEN_TIME       5000        // Time to keep door open in milliseconds

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

char *valueToWrite = "RFIDTest123456";  // Example value to write to the card
unsigned long doorOpenTime = 0;          // Tracks when the door was opened
bool isDoorOpen = false;                 // Track door state

void setup() {
  Serial.begin(9600);
  NFC_setup();
  pinMode(DOOR_PIN, OUTPUT);
  digitalWrite(DOOR_PIN, LOW);    // Ensure door starts locked
}

void loop() {
  // Check if door is open and should be closed
  if (isDoorOpen && (millis() - doorOpenTime >= OPEN_TIME)) {
    closeDoor();
  }

  // Always check for cards, whether door is open or not
  if (dect_card()) {
    if (compare_password()) {
      Serial.println(F("Authorized access"));
      openDoor();
    } else {
      Serial.println(F("Access denied"));
    }
    
    // Halt PICC and stop encryption
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }

  delay(100);  // Small delay to prevent excessive CPU usage
}

void openDoor() {
  digitalWrite(DOOR_PIN, HIGH);
  isDoorOpen = true;
  doorOpenTime = millis();
  Serial.println(F("Door opened"));
}

void closeDoor() {
  digitalWrite(DOOR_PIN, LOW);
  isDoorOpen = false;
  Serial.println(F("Door closed"));
}

// Your existing NFC_setup, writeDataToBlock, readDataFromBlock functions remain unchanged

bool compare_password() {
  // Prepare key - default key is FFFFFFFFFFFFh
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  Serial.println(F("**Card Detected:**"));
  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));

  // Perform read operation
  String readValue = readDataFromBlock(4);

  // Compare the read value with the expected value
  return (readValue == valueToWrite);
}

bool dect_card() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }

  // Select the card
  if (!mfrc522.PICC_ReadCardSerial()) {
    return false;
  }
  return true;
}