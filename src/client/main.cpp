#include <Arduino.h>
#include "Telegraph.h"

#define TX 2
#define RX 3

using namespace telegraph;

Telegraph wire = Telegraph();

byte res;
byte data[3] = {'1', '2', '3'};
byte b = 128;

void setup()
{
    Serial.begin(9600);
    wire.listen(3, 1);
    wire.talk(2, 100);
    wire.begin();
    // wire.await_all();
    delay(2000);
    wire.tx().send(data, 3);
}

void loop()
{
    if (wire.tx().buff_size() == 0) {
        wire.tx().send(data, 3);
    }
    wire.tick();
}
