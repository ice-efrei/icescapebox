#include <Arduino.h>
#include "Telegraph.h"

#define TX 2
#define RX 3

using namespace master;

Telegraph comm(TX);

byte i = 0;

void setup()
{
    Serial.begin(9600);
    comm.listen(RX);
    comm.begin(9600);
    comm.await_all();
}

void loop()
{
    comm.tick();
    if (comm.buff_size(0) > 0)
    {
        Serial.println(comm.read(0));
    }
}
