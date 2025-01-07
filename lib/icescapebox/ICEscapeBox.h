#ifndef ICESCAPEBOX_H
#define ICESCAPEBOX_H

#include <Arduino.h>
#include "Telegraph.h"

#define BAUD_RATE 220

#ifndef RX
#define RX 2
#endif

#ifndef TX
#define TX 3
#endif

#ifndef RUNNING_PIN
#define RUNNING_PIN 4
#endif

using client::Telegraph;

struct ieb_t {
    String serialNumber;
    int seed;
    unsigned long clockStartMs;
    Telegraph connection;
};

static ieb_t ICEscapeBox;

static bool _ended = false;

void begin()
{
    pinMode(RUNNING_PIN, OUTPUT);
    ICEscapeBox.connection = Telegraph(RX, TX);

    ICEscapeBox.connection.begin(BAUD_RATE);
    ICEscapeBox.connection.await();
    ICEscapeBox.connection.recv(sizeof(int));
    ICEscapeBox.clockStartMs = millis();

    int *s = &(ICEscapeBox.seed);

    for (unsigned short i = 0; i < sizeof(int); i++)
    {
        s[i] = ICEscapeBox.connection.read();
    }

    randomSeed(*s);

    ICEscapeBox.serialNumber = String(random(0x10000), HEX);
    while (ICEscapeBox.serialNumber.length() < 4)
    {
        ICEscapeBox.serialNumber = "0" + ICEscapeBox.serialNumber;
    }
}

void lost()
{
    byte _ = 0xff;
    ICEscapeBox.connection.write(&_, 1);
}

void won()
{
    byte _ = 0x00;
    ICEscapeBox.connection.write(&_, 1);
}

void update()
{
    ICEscapeBox.connection.tick();
}

void getTime(unsigned int *minutes, unsigned int *seconds, unsigned int *milliseconds)
{
    return;
}

#endif