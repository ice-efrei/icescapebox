// Initialisation des pins des LEDs
const int LED_GREEN = 9;
const int LED_YELLOW = 3;
const int LED_BLUE = 6;
const int LED_RED = 5;

// Initialisation des pins des boutons
const int BUTTON_GREEN = 0;
const int BUTTON_YELLOW = 0;
const int BUTTON_BLUE = 0;
const int BUTTON_RED = 0;

// Variables globales
String s = "";
int lives = 3, i = 0;
bool game = true;

// Fonction pour afficher les premières i lettres de la séquence avec les LEDs
void displaySequence(String s, int i) {
  for (int j = 0; j < i; j++) {
    int led = getLedFromNumber(s[j]); // Obtenir la LED à allumer
    digitalWrite(led, HIGH);
    delay(500); // Garde la LED allumée pendant 500 ms
    digitalWrite(led, LOW);
    delay(500); // Délai entre chaque LED
  }
}

// Retourne la pin LED correspondant à un numéro
int getLedFromNumber(char number) {
  switch (number) {
    case '0': return LED_GREEN;
    case '1': return LED_YELLOW;
    case '2': return LED_BLUE;
    case '3': return LED_RED;
    default: return -1; // Ne devrait jamais arriver
  }
}

// Vérifie si un bouton est pressé et retourne son numéro
int readButton() {
  if (digitalRead(LED_GREEN) == HIGH) return 0;
  if (digitalRead(LED_YELLOW) == HIGH) return 1;
  if (digitalRead(LED_BLUE) == HIGH) return 2;
  if (digitalRead(LED_RED) == HIGH) return 3;
  return -1; // Aucun bouton pressé
}

// Fait clignoter toutes les LEDs en cas d'erreur
void blinkAllLeds() {
  for (int k = 0; k < 5; k++) { // Clignote 5 fois
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
  // Configurer les LEDs comme sorties
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // Configurer les boutons comme entrées avec pull-up internes
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_RED, INPUT_PULLUP);

  // Génération de la séquence aléatoire
  randomSeed(analogRead(A0));
  for (int i = 0; i < 10; i++) {
    s += String(random(0, 4)); // Génère un chiffre entre 0 et 3
  }
}

void loop() {
  if (i < 10 && lives > 0) {
    displaySequence(s, i); // Affiche la séquence avec les LEDs
    int j = 0;
    game = true;

    while (game && j < i) {
      int buttonPressed = -1;

      // Attente qu'un bouton soit pressé
      while (buttonPressed == -1) {
        buttonPressed = readButton();
      }

      if (buttonPressed == s[j] - '0') { // Vérifie si le bouton correspond
        j++;
      } 
      else {
        blinkAllLeds(); // Erreur : clignotement de toutes les LEDs
        lives--;
        game = false; // Met fin à la séquence actuelle
      }

      // Petite pause pour éviter les doubles détections de boutons
      delay(300);
    }

    if (game) {
      i++; // Incrémenter uniquement si la séquence a été correctement complétée
    }
  } else {
    // Fin du jeu
    while (true) {
      ; // Boucle infinie pour terminer
    }
  }
}
