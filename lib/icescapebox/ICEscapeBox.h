#ifndef ICESCAPEBOX_H
#define ICESCAPEBOX_H

#include <Arduino.h>
#include "Telegraph.h"
#include "IEBRandom.h"

#define BAUD_RATE 220

#ifndef RX
#define RX 3
#endif

#ifndef TX
#define TX 2
#endif

telegraph::Telegraph wire = telegraph::Telegraph();

void getSeed()
{
    wire.listen(RX, 100);
    wire.talk(TX, 100);
    wire.begin();
    wire.await_all();
    wire.rx().recieve(sizeof(int));

    _syncms = millis();

    byte *seed_arr = (byte *)&seed;
    byte counter = 0;

    while (wire.rx().buff_size() != 0)
    {
        seed_arr[counter] = wire.rx().read();
        counter++;
    }

    genRandomsValues(seed, false);
}

void lost()
{
    wire.tx().tell(0x0);
}

void won()
{
    wire.tx().tell(0xf);
}

void lostLife(unsigned short n)
{
    wire.tx().tell(0x8 + (n & 0x3));
}

void lostLife()
{
    wire.tx().tell(0x9);
}

#endif