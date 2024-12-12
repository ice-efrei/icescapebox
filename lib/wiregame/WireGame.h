#ifndef WIREGAME_H
#define WIREGAME_H

#include <Arduino.h>

#include "GameSeed.h"

#define NUM_WIRE 6

const String colorsStr[] = { "white", "red", "yellow", "blue", "black" };

enum Color {
  white,
  red,
  yellow,
  blue,
  black
};

class WireGame {
    public:
        WireGame(int pins[NUM_WIRE], GameSeed& seed);
        Color wireList[NUM_WIRE];
        int wireCount;
        int wireToCut;
        void begin();
        int checkWin();
        void waitForConnections();
        String colorToStr(Color c);
    private:
        GameSeed& _seed;
        int _pins[NUM_WIRE];
        int determineWireToCut();
};

#endif
