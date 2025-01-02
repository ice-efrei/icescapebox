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
    comm.begin(9600);
    comm.await();
    randomSeed(analogRead(0));
}

void loop()
{
    byte data = 25;
    data = random(255);
    comm.write(&data, 1);
    Serial.println(data);
    delay(1000);
}
