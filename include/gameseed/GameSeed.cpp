#include <limits.h>
#include "GameSeed.h"

GameSeed::GameSeed(int pin) {
    _pin = pin;
}

int GameSeed::getSeed() {
    pinMode(_pin, INPUT);
    int seed = analogRead(_pin);
    // Remove last 3 bits as they aren't stable
    seed = seed & (INT_MAX ^ 7);
    // Shift 3 bits to right (overwrite the 3 bits set to 0)
    seed = seed >> 3;

    return seed;
}

void GameSeed::begin() {
    read();

    randomSeed(seed);

    // Generate a random 4-digit serial number in base 16
    serialNumber = String(random(0x10000), HEX);
    while (serialNumber.length() < 4) {
        serialNumber = "0" + serialNumber;
    }
}

int GameSeed::read() {
    seed = getSeed();
    return seed;
}
