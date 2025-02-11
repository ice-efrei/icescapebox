#include <Arduino.h>


// Initialisation des pins des LEDs
const int LED_GREEN = 13;
const int LED_YELLOW = 2;
const int LED_BLUE = 11;
const int LED_RED = 7;

// Initialisation des pins des boutons
const int BUTTON_GREEN = 9;
const int BUTTON_YELLOW = 3;
const int BUTTON_BLUE = 6;
const int BUTTON_RED = 5;

// Variables globales
String s = ""; // Séquence à reproduire
int lives = 3, i = 0;
bool game = true;

// Fonction pour afficher les premières i lettres de la séquence avec les LEDs
void displaySequence(String s, int i) {
  for (int j = 0; j < i; j++) {
    int led = getLedFromNumber(s[j]);
    Serial.print("LED lit: ");
    Serial.println(led);
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
  }
}

// Retourne la pin LED correspondant à un numéro
int getLedFromNumber(char number) {
  switch (number) {
    case '0': return LED_GREEN;
    case '1': return LED_YELLOW;
    case '2': return LED_BLUE;
    case '3': return LED_RED;
    default: return -1;
  }
}

// Retourne le bouton correct en fonction de la LED allumée et du nombre d'erreurs
int getCorrectButton(char led, int errors) {
  if (led == '0') return (errors == 0) ? BUTTON_BLUE : (errors == 1) ? BUTTON_YELLOW : BUTTON_GREEN;
  if (led == '1') return (errors == 0) ? BUTTON_RED : (errors == 1) ? BUTTON_GREEN : BUTTON_RED;
  if (led == '2') return (errors == 0) ? BUTTON_YELLOW : (errors == 1) ? BUTTON_BLUE : BUTTON_YELLOW;
  if (led == '3') return (errors == 0) ? BUTTON_GREEN : (errors == 1) ? BUTTON_RED : BUTTON_BLUE;
  return -1;
}

// Vérifie si un bouton est pressé et retourne son numéro
int readButton() {
  if (digitalRead(BUTTON_GREEN) == LOW) return 0;
  if (digitalRead(BUTTON_YELLOW) == LOW) return 1;
  if (digitalRead(BUTTON_BLUE) == LOW) return 2;
  if (digitalRead(BUTTON_RED) == LOW) return 3;
  return -1;
}

// Fait clignoter toutes les LEDs en cas d'erreur
void blinkAllLeds() {
  for (int k = 0; k < 5; k++) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, HIGH);
    delay(200);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);
    delay(200);
  }
}

void setup() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_RED, INPUT_PULLUP);

// Initialization of serial communication and random number generator
  Serial.begin(9600);
  randomSeed(analogRead(A0));

  for (int i = 0; i < 10; i++) {
    s += String(random(0, 4));
  }
}

void loop() {
  if (i < 10 && lives > 0) {
    displaySequence(s, i);
    int j = 0;
    game = true;

    while (game && j < i) {
      int buttonPressed = -1;
      int correctButton = getCorrectButton(s[j], 3 - lives); // 3 - lives = number of errors

      Serial.print("Correct button to press: ");
      Serial.println(correctButton);

      while (buttonPressed == -1) {
        buttonPressed = readButton();
        if (buttonPressed != -1) {
          Serial.print("Button pressed: ");
          Serial.println(buttonPressed);
          digitalWrite(getLedFromNumber(s[j]), HIGH);
          delay(500);
          digitalWrite(getLedFromNumber(s[j]), LOW);
        }
      }

      if (buttonPressed == correctButton) {
        j++;
      } else {
        blinkAllLeds();
        lives--;
        game = false;
      }

      delay(300);
    }

    if (game) {
      i++;
    }
  } else {
    while (true) {
      ;
    }
  }
}
