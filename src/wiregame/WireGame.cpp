#include <Arduino.h>
#include "GameSeed.h"
#include "wiregame/WireGame.h"

int removeElement(int *array, int index, int *size) {
    int res = array[index];
    // lowkey need a goth mommy rn
    for(int i = index; i < *size - 1; i++) array[i] = array[i + 1];
    *size = *size - 1;
    return res;
}

// Flemme de malloc et tout alors on utilise un array du stack
void range(int *array, int start, int n) {
    if(n > WIRE_COUNT) return;
    for(int i = 0; i < n; i++) {
        array[i] = start + i;
    }
}

void swap(int *a, int *b) {
    // im just a chill guy who don't like tmp variables
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

// BUBBLE SORT BABYYYY
void sortWires(wire_t *wires, int size) {
    for(int i = size - 1; i >= 0; i--)  {
        for(int j = 0; j < i; j++) {
            if(wires[j].pin > wires[j + 1].pin) {
                swap(&(wires[j].pin), &(wires[j + 1].pin));
            }   
        }
    }
}

WireGame::WireGame(int pins[WIRE_COUNT], RGBLed& led, GameSeed& seed): _led(led), _seed(seed) {
    for(int i = 0; i < WIRE_COUNT; i++) {
        _pins[i] = pins[i];
    }
}

void WireGame::generateWires() {
    // Generate a random number of wires between 3 and 6
    wireCount = 3 + random(4);

    int availablePins[WIRE_COUNT];

    for(int i = 0; i < WIRE_COUNT; i++) {
        availablePins[i] = _pins[i];
    }

    int size = WIRE_COUNT;

    // Generate a random list of colors
    for (int i = 0; i < wireCount; i++) {
        wire_t wire;
        wire.color = (Color)random(5);
        wire.index = i;
        wire.pin = removeElement(availablePins, random(WIRE_COUNT - i), &size);
        wireList[i] = wire;
    }

    sortWires(wireList, wireCount);
}

void WireGame::begin() {

    for (int i = 0; i < WIRE_COUNT; i++) {
        pinMode(_pins[i], INPUT_PULLUP);
    }

    generateWires();

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

// Écrit par Eliott (et reprise un peu par moi) si vous avez des revendications c'est pour lui
wire_t WireGame::determineWireToCut() {
    bool hasRed = false;
    bool hasBlack = false;
    bool hasYellow = false;
    int lastRedIndex = -1;
    int lastBlueIndex = -1;
    int blueCount = 0;
    int yellowCount = 0;
    int whiteCount = 0;

    for (int i = 0; i < wireCount; i++) {
        if (wireList[i].color == red) {
            hasRed = true;
            lastRedIndex = i;
        }
        if (wireList[i].color == blue) {
            blueCount++;
            lastBlueIndex = i;
        }
        if (wireList[i].color == yellow) {
            yellowCount++;
        }
            if (wireList[i].color == white) {
            whiteCount++;
        }
        if (wireList[i].color == black) {
            hasBlack = true;
        }
    }

    int lastDigit = strtol(_seed.serialNumber.substring(_seed.serialNumber.length() - 1).c_str(), NULL, 16);

    if (wireCount == 3) {
        if (!hasRed) {
            return wireList[1];  // Cut the second wire
        } else if (wireList[2].color == white) {
            return wireList[2];  // Cut the last wire
        } else if (blueCount > 1) {
            return wireList[lastBlueIndex];  // Cut the last blue wire
        } else {
            return wireList[2];  // Cut the last wire
        }
    } else if (wireCount == 4) {
        if (hasRed && (lastDigit % 2 != 0)) {
            return wireList[lastRedIndex];  // Cut the last red wire
        } else if (wireList[3].color == yellow && !hasRed) {
            return wireList[0];  // Cut the first wire
        } else if (blueCount == 1) {
            return wireList[0];  // Cut the first wire
        } else if (yellowCount > 1) {
            return wireList[3];  // Cut the last wire
        } else {
            return wireList[1];  // Cut the second wire
        }
    } else if (wireCount == 5) {
        if (wireList[4].color == black && (lastDigit % 2 != 0)) {
            return wireList[3];  // Cut the fourth wire
        } else if (hasRed && yellowCount > 1) {
            return wireList[0];  // Cut the first wire
        } else if (!hasBlack) {
            return wireList[1];  // Cut the second wire
        } else {
            return wireList[0];  // Cut the first wire
        }
    } else if (wireCount == 6) {
        if (!hasYellow && (lastDigit % 2 != 0)) {
            return wireList[2];  // Cut the third wire
        } else if (yellowCount == 1 && whiteCount > 1) {
            return wireList[3];  // Cut the fourth wire
        } else if (!hasRed) {
            return wireList[5];  // Cut the last wire
        } else {
            return wireList[3];  // Cut the fourth wire
        }
    }

  return wireList[0];  // Should never reach here
}

int WireGame::checkWin() {
    int c = 0;
    for (int i = 0; i < wireCount; i++) {
        int state = digitalRead(_pins[i]);
        if (state == HIGH && _pins[i] != wireToCut.pin) {
            return -1;
        }
        if(state == HIGH && _pins[i] == wireToCut.pin) {
            c += 1;
        }
    }
    return c;
}

void WireGame::connectWires() {
    for(int i = 0; i < wireCount; i++) {
        Serial.print("Wire ");
        Serial.print(colorToStr(wireList[i].color));
        Serial.print(" at pin ");
        Serial.println(wireList[i].pin);

        _led.reset();
        delay(500);
        _led.color(wireList[i].color);

        int c = true;
        while(c) {
            c = digitalRead(wireList[i].pin);
            delay(100);
        }
    }

    _led.reset();
}

// --------

RGBLed::RGBLed(int R_G_B_pins[3]) {
    redPin = R_G_B_pins[0];
    greenPin = R_G_B_pins[1];
    bluePin = R_G_B_pins[2];
    _red = 0;
    _green = 0;
    _blue = 0;
}

void RGBLed::begin() {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    reset();
}

void RGBLed::update() {
    digitalWrite(redPin, !_red);
    digitalWrite(greenPin, !_green);
    digitalWrite(bluePin, !_blue);
}

void RGBLed::reset() {
    red(LOW);
    blue(LOW);
    green(LOW);
}

// WireGame specific function
void RGBLed::color(Color c) {
    reset();
    switch(c) { 
        case 0: // White
            red(HIGH);
            blue(HIGH);
            green(HIGH);
            break;
        case 1: // Red
            red(HIGH);
            break;
        case 2: // Yellow
            red(HIGH);
            green(HIGH);
            break;
        case 3: // Blue
            blue(HIGH);
            break;
        case 4: // Black
            // Green is black
            green(HIGH);
            break;
    }
}
