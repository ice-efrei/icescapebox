char answer[11] = ""; // 10 caractères + '\0'
bool Game = true;
int i = 0;
int lives = 3;

void setup() {
  Serial.begin(9600);
  // Génération de la séquence aléatoire
  for (int j = 0; j < 10; j++) {
    int randomNumber = rand() % 4; // Génère un nombre entre 0 et 3
    char c = '0' + randomNumber;  // Convertit en caractère ('0', '1', '2', '3')
    answer[j] = c;                // Ajoute directement au tableau
  }
  answer[10] = '\0'; // Termine la chaîne
  Serial.println("Jeu démarré !");
  Serial.println("Entrez les nombres un par un.");
}

void loop() {
  if (Game && i < 10) {
    Serial.print("Votre séquence actuelle : ");
    Serial.println(answer); // Pour afficher la séquence complète

    // Lecture de l'entrée utilisateur
    if (Serial.available() > 0) {
      int numero = Serial.parseInt(); // Récupère un nombre entier depuis le port série

      if (numero == (answer[i] - '0')) { // Convertit le caractère à un entier et compare
        i++;
        Serial.println("Correct !");
      } else {
        lives--;
        Serial.println("Incorrect !");
        if (lives == 0) {
          Game = false;
        }
      }
    }
  }

  // Fin du jeu
  if (!Game) {
    Serial.println("Raté ! Vous avez perdu.");
    while (true); // Stoppe le programme
  } else if (i == 10) {
    Serial.println("Bien joué ! Vous avez gagné.");
    while (true); // Stoppe le programme
  }
}
