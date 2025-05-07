#include <Arduino.h>

const int pinCLK = 12;
const int pinDT = 13;
const int pinSW = 11;

int lastCLKState;
int counter = 0;
bool buttonPressed = false;

void setup() {
    pinMode(pinCLK, INPUT);
    pinMode(pinDT, INPUT);
    pinMode(pinSW, INPUT_PULLUP);  // Pull-up pour le bouton
    
    Serial.begin(9600);
    lastCLKState = digitalRead(pinCLK);
}

void loop() {
    // Gestion de l'encodeur rotatif
    int currentCLKState = digitalRead(pinCLK);
    if (currentCLKState != lastCLKState) {
        if (digitalRead(pinDT) != currentCLKState) {
            counter++;
        } else {
            counter--;
        }
        Serial.print("Valeur encodeur : ");
        Serial.println(counter);
    }
    lastCLKState = currentCLKState;
    
    // Gestion du bouton intégré
    if (digitalRead(pinSW) == LOW && !buttonPressed) {
        buttonPressed = true;
        Serial.println("Bouton appuyé !");
    } else if (digitalRead(pinSW) == HIGH && buttonPressed) {
        buttonPressed = false;
    }
    
    delay(1); // Petit délai pour lisser les lectures
}