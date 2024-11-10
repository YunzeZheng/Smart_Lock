#include <Keypad.h>
#include "main.h"

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};

char characterKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {3, 2, 1, 0};
byte colPins[COLS] = {7, 6, 5, 4};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


void Keypad_setup() {
  Serial.println("Enter a string using the keypad(# - clear , * - backspace):");
}

String StringInput() {
  char key = customKeypad.getKey();
  if (key) {
    if (key == '#') {  // If the "#" key is pressed, finalize the input
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
  return inputString;
}
