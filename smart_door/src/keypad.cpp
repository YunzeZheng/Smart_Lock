#include <Keypad.h>
#include "main.h"

const byte ROWS = 4;
const byte COLS = 4;

char SecKeys[ROWS][COLS] = {
  {'E','F','G','H'},
  {'I','G','K','L'},
  {'M','N','O','P'},
  {'*','Q','#','R'}
};

char Keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {14, 15, 16, 17};

Keypad customKeypad = Keypad(makeKeymap(Keys), rowPins, colPins, ROWS, COLS);
Keypad ccustomKeypad2 = Keypad(makeKeymap(SecKeys), rowPins, colPins, ROWS, COLS);


void Keypad_setup() {
  Serial.println("Enter a string using the keypad(# - clear , * - backspace, D - finih):");
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}
String StringInput() {
  char key;
  String inputString = "";
  while (true) {
    key = customKeypad.getKey();
    if (key) {
      if (key == 'D') {
        Serial.println("Input complete.");
        break;  
      }
      else if (key == '#') {
        Serial.print("Entered: ");
        Serial.println(inputString);
        inputString = "";
      }
      else if (key == '*') {
        if (inputString.length() > 0) {
          inputString.remove(inputString.length() - 1);
        }
      }
      else {
        inputString += key;
      }
      Serial.println(inputString);
    }
  }
  return inputString;
}