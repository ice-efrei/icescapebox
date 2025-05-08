#ifndef IEBRANDOM_H
#define IEBRANDOM_H

#include <Arduino.h>

int seed;
char serialNumber[9];
unsigned long _syncms = 0;

void genRandomsValues(int s, bool syncclock = true)
{
    const char letters[] = "AABCDEEFGHIIJKLMNPQRSTUUVWXZ"; // 28 chars
    const char digits[] = "0123456789";

    if (syncclock) {
        _syncms = millis();
    }

    seed = s;
    randomSeed(seed);
    byte len = random(3, 9);
    serialNumber[len] = 0;
    bool hasdigit = false;
    for (byte i = 0; i < len; i++)
    {
        if (random(2))
        {
            serialNumber[i] = digits[random(10)];
            hasdigit = true;
        }
        else
        {
            serialNumber[i] = letters[random(28)];
        }
    }
    if (!hasdigit) {
        byte pos = random(len);
        serialNumber[len] = digits[random(10)];
    }
}

unsigned long ms()
{
    return millis() - _syncms;
}

#endif