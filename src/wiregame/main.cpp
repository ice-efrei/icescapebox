#include "GameSeed.h"
#include "wiregame/WireGame.h"

int wirePins[WIRE_COUNT] = { 2, 3, 4, 5, 6, 7 };  // Digital pins connected to the wires
int ledPins[3] = { 12, 11, 10 };
GameSeed seed(A0);
RGBLed led(ledPins);
WireGame game(wirePins, led, seed);

int ended = 0;

void setup() {
    Serial.begin(9600);

    Serial.println("\nBEGIN\n");

    seed.begin();
    led.begin();

    game.begin();

    Serial.print("Seed : ");
    Serial.println(seed.seed);

    Serial.print(game.wireCount);
    Serial.println(" wires to connect");
    
    Serial.print("Serial Number: ");
    Serial.println(seed.serialNumber);

    Serial.print("Cut the ");
    Serial.print(game.colorToStr(game.wireToCut.color));
    Serial.print(" wire at pin ");
    Serial.println(game.wireToCut.pin);

    game.connectWires();

    Serial.println("All cables connected");

    delay(1000);
}

void loop() {

    if(!ended) {
        ended = 1;
        switch(game.checkWin()) {
            case -1:
                Serial.println("You lose :(");
                led.reset();
                led.red(1);
                break;
            case 1:
                Serial.println("You win :)");
                led.reset();
                led.green(1);
                break;
            default : 
                ended = 0;
                break;
        }
    }

    delay(100);  // Check every second
}