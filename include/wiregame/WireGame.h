#ifndef WIREGAME_H
#define WIREGAME_H

#include <Arduino.h>

#include "GameSeed.h"

#define WIRE_COUNT 6

const String colorsStr[] = { "white", "red", "yellow", "blue", "black" };

enum Color {
  white,
  red,
  yellow,
  blue,
  black
};

typedef struct {
    Color color;
    int pin;
    int index;
} wire_t;

class RGBLed;
class WireGame;

class WireGame {
    public:
        WireGame(int pins[WIRE_COUNT], RGBLed& led, GameSeed& seed);
        int wireCount;
        wire_t wireList[WIRE_COUNT];
        wire_t wireToCut;
        void begin();
        int checkWin();
        void connectWires();
        String colorToStr(Color c);
    private:
        RGBLed& _led;
        GameSeed& _seed;
        void generateWires();
        int _pins[WIRE_COUNT];
        wire_t determineWireToCut();
};

class RGBLed {
    public:
        RGBLed(int R_G_B_pins[3]);
        void begin();
        void update();
        int pins[3];
        int red() const { return _red; };
        void red(int red) { _red = red; update(); };
        int green() const { return _blue; };
        void green(int green) { _green = green; update(); };
        int blue() const { return _blue; };
        void blue(int blue) { _blue = blue; update(); };
        void color(Color c);
        void reset();
    private:
        int redPin;
        int greenPin;
        int bluePin;
        int _red;
        int _green;
        int _blue;
};

#endif