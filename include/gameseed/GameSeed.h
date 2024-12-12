#ifndef GAMESEED_H
#define GAMESEED_H

#include <Arduino.h>

class GameSeed {
    public:
        GameSeed(int pin);
        String serialNumber;
        int seed;
        void begin();
        int read();
    private:
        int _pin;
        int getSeed();
};


#endif
