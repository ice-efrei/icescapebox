/**
 * @author Grégoire Badiche
 */

#include "GameSeed.h"

#define MED_READ 15
#define MED_READ_2 (MED_READ / 2)

GameSeed::GameSeed(int pin) {
    _pin = pin;
}

void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void bubbleSort(int *array, int size) {
    for(int i = size - 1; i >= 0; i--) {
        for(int j = 0; j < i; j++) {
            if(array[j] > array[j + 1]) {
                swap(&(array[j]), &(array[j + 1]));
            }
        }
    }
}

int GameSeed::getSeed() {
    pinMode(_pin, INPUT);

    int readings[MED_READ];

    for(int i = 0; i < MED_READ; i++) {
        readings[i] = analogRead(_pin);
        readings[i] = readings[i] >> 1;
        delay(10);
    }

    bubbleSort(readings, MED_READ);

    // Take the median
    int seed = readings[MED_READ_2];

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