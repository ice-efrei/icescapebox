#include <Arduino.h>
#include <Keypad.h>
#include "TM1637Display.h"

const byte ROWS = 4; // Quatre lignes
const byte COLS = 4; // Quatre colonnes
// Définir les symboles sur les boutons du clavier
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','F'},
  {'4','5','6','E'},
  {'7','8','9','D'},
  {'A','0','B','C'}
};
byte rowPins[ROWS] = {29, 27, 25, 23}; // Connecter aux lignes du clavier
byte colPins[COLS] = {37, 35, 33, 31}; // Connecter aux colonnes du clavier

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Pins definitions for TM1637 and can be changed to other ports
const int CLK = 2;
const int DIO = 3;
TM1637D tm1637(CLK, DIO);

String inputString = ""; // Variable pour stocker les caractères saisis
bool displayActive = false; // Variable pour indiquer si l'afficheur doit être actif

void setup(){
  Serial.begin(9600);
  tm1637.init(); // Initialiser l'écran TM1637
}

void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    if (inputString.length() < 4) { // Vérifier si la longueur de la chaîne est inférieure à 4
      inputString += customKey; // Ajouter le caractère saisi à la chaîne
      displayActive = true; // Activer l'afficheur dès qu'une entrée est donnée
    } else {
      inputString = "";
      displayActive = false; // Réinitialiser la chaîne si elle dépasse 4 caractères
    }
    Serial.println(inputString); // Afficher la chaîne sur le moniteur série
    if (displayActive) {
      displayString(inputString); // Afficher la chaîne sur l'écran TM1637 si l'afficheur est actif
    }
  } else {
    displayActive = false; // Désactiver l'afficheur si aucune entrée n'est donnée
  }
}

void displayString(String str) {
  str.toUpperCase(); // Convertir la chaîne en majuscules
  tm1637.display(0, str.charAt(0)); // Afficher le premier caractère
  tm1637.display(1, str.charAt(1)); // Afficher le deuxième caractère
  tm1637.display(2, str.charAt(2)); // Afficher le troisième caractère
  tm1637.display(3, str.charAt(3)); // Afficher le quatrième caractère
}
