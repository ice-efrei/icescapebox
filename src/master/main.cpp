#include <Arduino.h>
#include "Telegraph.h"

#define TX 2
#define RX 3

using namespace master;

Telegraph comm(TX);

byte i = 0;
String a = "abc";

void setup()
{
    Serial.begin(9600);
    comm.listen(RX);
    comm.begin(100);
    comm.await_all();
}

void loop()
{
    comm.tick();
    if (comm.buff_size(0) > 2)
    {
        a[0] = comm.read(0);
        a[1] = comm.read(0);
        a[2] = comm.read(0);
        Serial.println(a);
    }
}
