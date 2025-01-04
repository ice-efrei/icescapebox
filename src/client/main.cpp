#include <Arduino.h>
#include "Telegraph.h"

#define TX 2
#define RX 3

using namespace client;

Telegraph comm(RX, TX);

byte res;

void setup()
{
    Serial.begin(9600);
    comm.begin(100);
    comm.await();
    randomSeed(analogRead(0));
}

void loop()
{
    byte data[3] = {'h', 'i', '!'};
    comm.write(data, 3);
}
