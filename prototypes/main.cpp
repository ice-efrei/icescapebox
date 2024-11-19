#include <Keypad.h>
#include <TM1637Display.h>

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns
// define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','F'},
  {'4','5','6','E'},
  {'7','8','9','D'},
  {'A','0','B','C'}
};
byte rowPins[ROWS] = {29, 27, 25, 23}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {37, 35, 33, 31}; // connect to the column pinouts of the keypad

// initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
TM1637Display display(2, 3);

String inputString = ""; // Variable to store the input string

void displayString(String str);

void setup() {
  Serial.begin(9600);
  display.setBrightness(0x0f); // Set the brightness of the display
}

void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey) {
    Serial.println(customKey);
    if (customKey >= '0' && customKey <= '9') { // Only consider numeric input
      if (inputString.length() < 4) { // Ensure the input string does not exceed 4 characters
        inputString += customKey;
      }
    } else if (customKey == 'C') { // Handle the 'C' key to delete the last character
      if (inputString.length() > 0) {
        inputString.remove(inputString.length() - 1);
      }
    }
    displayString(inputString);
  }
}

void displayString(String str) {
  uint16_t number = str.toInt(); // Convert the string to an integer
  display.showNumberDec(number, false, 4, 0); // Display the number on the TM1637
}