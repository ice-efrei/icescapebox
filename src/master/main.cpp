#include <Arduino.h>
#include "Telegraph.h"

#define TX 2
#define RX 3

using namespace telegraph;

Telegraph wire = Telegraph();

byte res;
byte data[3] = {'h', 'i', '!'};

void setup()
{
    Serial.begin(9600);
    wire.listen(3, 100);
    wire.listen(4, 100);
    wire.talk(2, 100);
    wire.begin();
    Serial.println("waiting");
    wire.await_all();
    Serial.println("ready");
}

void loop()
{
    for (unsigned short i = 0; i < wire.n_listeners; i++) {
        if (wire.rxs(i).buff_size() != 0) {
            Serial.print("buff size : ");
            Serial.print(wire.rxs(i).buff_size());
            Serial.print(", wire ");
            Serial.print(i);
            Serial.print(" said ");
            Serial.println((char) wire.rxs(i).read());
        }
    }
    wire.tick();
}
