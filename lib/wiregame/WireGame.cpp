#include <Arduino.h>
#include "GameSeed.h"
#include "WireGame.h"

WireGame::WireGame(int pins[NUM_WIRE], GameSeed& seed): _seed(seed) {
    for(int i = 0; i < NUM_WIRE; i++) {
        _pins[i] = pins[i];
    }
}

void WireGame::begin() {

    for (int i = 0; i < NUM_WIRE; i++) {
        pinMode(_pins[i], INPUT_PULLUP);
    }

    // Generate a random number of wires between 3 and 6
    wireCount = 3 + random(4);

    // Generate a random list of colors
    for (int i = 0; i < wireCount; i++) {
        wireList[i] = (Color)random(5);
        Serial.println(colorToStr(wireList[i]));
    }

    wireToCut = determineWireToCut();
}

String WireGame::colorToStr(Color c) {
    switch(c) {
        case white : return "white";
        case red: return "red";
        case yellow : return "yellow";
        case blue : return "blue";
        case black : return "black";
        default : return "black";
    }
}

int WireGame::determineWireToCut() {
    bool hasRed = false;
    bool hasBlack = false;
    bool hasYellow = false;
    int lastRedIndex = -1;
    int lastBlueIndex = -1;
    int blueCount = 0;
    int yellowCount = 0;
    int whiteCount = 0;

    for (int i = 0; i < wireCount; i++) {
        if (wireList[i] == red) {
            hasRed = true;
            lastRedIndex = i;
        }
        if (wireList[i] == blue) {
            blueCount++;
            lastBlueIndex = i;
        }
        if (wireList[i] == yellow) {
            yellowCount++;
        }
            if (wireList[i] == white) {
            whiteCount++;
        }
        if (wireList[i] == black) {
            hasBlack = true;
        }
    }

    int lastDigit = strtol(_seed.serialNumber.substring(_seed.serialNumber.length() - 1).c_str(), NULL, 16);

    if (wireCount == 3) {
        if (!hasRed) {
            return 1;  // Cut the second wire
        } else if (wireList[2] == white) {
            return 2;  // Cut the last wire
        } else if (blueCount > 1) {
            return lastBlueIndex;  // Cut the last blue wire
        } else {
            return 2;  // Cut the last wire
        }
    } else if (wireCount == 4) {
        if (hasRed && (lastDigit % 2 != 0)) {
            return lastRedIndex;  // Cut the last red wire
        } else if (wireList[3] == yellow && !hasRed) {
            return 0;  // Cut the first wire
        } else if (blueCount == 1) {
            return 0;  // Cut the first wire
        } else if (yellowCount > 1) {
            return 3;  // Cut the last wire
        } else {
            return 1;  // Cut the second wire
        }
    } else if (wireCount == 5) {
        if (wireList[4] == black && (lastDigit % 2 != 0)) {
            return 3;  // Cut the fourth wire
        } else if (hasRed && yellowCount > 1) {
            return 0;  // Cut the first wire
        } else if (!hasBlack) {
            return 1;  // Cut the second wire
        } else {
            return 0;  // Cut the first wire
        }
    } else if (wireCount == 6) {
        if (!hasYellow && (lastDigit % 2 != 0)) {
            return 2;  // Cut the third wire
        } else if (yellowCount == 1 && whiteCount > 1) {
            return 3;  // Cut the fourth wire
        } else if (!hasRed) {
            return 5;  // Cut the last wire
        } else {
            return 3;  // Cut the fourth wire
        }
    }

  return -1;  // Should never reach here
}

int WireGame::checkWin() {
    int c = 0;
    for (int i = 0; i < wireCount; i++) {
        int state = digitalRead(_pins[i]);
        if (state == HIGH && i != wireToCut) {
            return -1;
        }
        if(state == HIGH && i == wireToCut) {
            c += 1;
        }
    }
    if(c > 0)
        return 1;
    return 0;
}

void WireGame::waitForConnections() {
    int s = 0;
    while (s != wireCount) {
        s = 0;
        for (int i = 0; i < wireCount; i++) {
            if (digitalRead(_pins[i]) == LOW) {
                s += 1;
            }
        }
        for(int i = wireCount; i < NUM_WIRE; i++) {
            if (digitalRead(_pins[i]) == LOW) {
                s -= 1;
            }
        }
    }
}
