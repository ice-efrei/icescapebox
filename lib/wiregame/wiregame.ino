#include "GameSeed.h"
#include "WireGame.h"

int wirePins[NUM_WIRE] = { 2, 3, 4, 5, 6, 7 };  // Digital pins connected to the wires
GameSeed seed(A0);
WireGame game(wirePins, seed);

int ended = 0;

void setup() {
    Serial.begin(9600);

    Serial.println("\nBEGIN\n");

    seed.begin();

    game.begin();

    Serial.print("Seed : ");
    Serial.println(seed.seed);

    Serial.print(game.wireCount);
    Serial.println(" wires to connect");
    
    Serial.print("Serial Number: ");
    Serial.println(seed.serialNumber);

    Serial.print("Cut the ");
    Serial.print(game.colorToStr(game.wireList[game.wireToCut]));
    Serial.print(" wire at index ");
    Serial.println(game.wireToCut);

    game.waitForConnections();
    Serial.println("All cables connected");
}

void loop() {

    if(!ended) {
        ended = 1;
        switch(game.checkWin()) {
            case -1:
                Serial.println("You lose :(");
                break;
            case 1:
                Serial.println("You win :)");
                break;
            default : 
                ended = 0;
                break;
        }
    }

    delay(100);  // Check every second
}
