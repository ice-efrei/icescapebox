#ifndef SWITCH_H
#define SWITCH_H

#include <Arduino.h>
#include <EEPROM.h>

// Pin Definitions
const int switchPins[5] = {2, 3, 4, 5, 6};
const int ledPins[5] = {7, 8, 9, 10, 11};
const int encoderPinA = 12;
const int encoderPinB = 13;

// Game Variables
int ledStates[5] = {0, 0, 0, 0, 0};
int switchStates[5] = {0, 0, 0, 0, 0};
int switchToLED[5][5]; // 5x5 matrix (LEDs x Switches)
int encoderValue = 0;
int lastEncoderValue = 0;

// Function to apply XOR logic gate
bool applyXOR(bool ledState, bool switchState) {
    return ledState ^ switchState;
}

// Function to generate a random 5x5 matrix based on a seed
void generateMatrix(int seed) {
    randomSeed(seed);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            switchToLED[i][j] = random(0, 2); // 0 = No effect, 1 = XOR effect
        }
    }
}

// // Read rotary encoder and set seed
// void readEncoder() { // TODO: Implement rotary encoder properly
//     int aState = digitalRead(encoderPinA);
//     int bState = digitalRead(encoderPinB);
//     if (aState != lastEncoderValue) {
//         if (bState != aState) {
//             encoderValue++;
//         } else {
//             encoderValue--;
//         }
//         generateLogicMappings(abs(encoderValue)); // Update logic mappings with new seed
//     }
//     lastEncoderValue = aState;
// }

// placeholder function because we don't have an encoder yet
void readEncoder() {
    encoderValue = 0;
}

// Read switches and update LEDs
void updateLEDs() {
    static int previousSwitchStates[5] = {HIGH, HIGH, HIGH, HIGH, HIGH};
    static unsigned long lastDebounceTime[5] = {0, 0, 0, 0, 0};
    const unsigned long debounceDelay = 50; // 50ms debounce time

    for (int i = 0; i < 5; i++) {
        int currentState = digitalRead(switchPins[i]); // Read switch state

        if (currentState != previousSwitchStates[i]) {
            lastDebounceTime[i] = millis(); // Reset debounce timer
        }

        if ((millis() - lastDebounceTime[i]) > debounceDelay) { // Wait for stable state
            if (currentState != switchStates[i]) { // State has changed
                switchStates[i] = currentState;
                
                // XOR toggle LEDs based on the switch-to-LED matrix
                for (int j = 0; j < 5; j++) {
                    if (switchToLED[i][j] == 1) {
                        ledStates[j] = applyXOR(ledStates[j], 1);
                        digitalWrite(ledPins[j], ledStates[j]);
                    }
                }
            }
        }

        previousSwitchStates[i] = currentState; // Update last state
    }
}


// Check win condition
bool checkWinCondition() {
    for (int i = 0; i < 5; i++) {
        if (ledStates[i] == LOW) return false;
    }
    return true;
}


#endif // SWITCH_H