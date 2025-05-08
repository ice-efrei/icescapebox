#include <Arduino.h>
#include "Telegraph.h"
#include "TM1650.h"
#include "IEBRandom.h"

#define TX 2
#define RX 3

using namespace telegraph;

Telegraph wire = Telegraph();

TM1650 clock(9, 10, 4);

byte lifes = 3;

const int totalTime = 6000;

void updateClock() {
    int nTime = totalTime - (ms() / 10) % 10000;
    clock.setDisplayToDecNumber(nTime, 0x4);
    const int mil = nTime % 100;
    if (mil < 2) {
        digitalWrite(12, HIGH);
    } else {
        digitalWrite(12, LOW);
    }
}

void waitForStart() {

}

void explode() {
    Serial.println("Exploding!");
}

void disarm() {
    Serial.println("Disarming!");
}

void setup()
{
    Serial.begin(9600);
    wire.listen(3, 100);
    wire.listen(4, 100);

    wire.talk(2, 100);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    wire.begin();
    Serial.println("waiting");

    waitForStart();

    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("ready");
    seed = analogRead(0);

    wire.tx().tell((byte *)&seed, sizeof(seed));
    
    genRandomsValues(seed);

    Serial.print("Random seed is ");
    Serial.print(seed);
    Serial.print(", serial number is ");
    Serial.print(serialNumber);
    Serial.print(", ms is ");
    Serial.println(ms());

    clock.setupDisplay(true, 7);

}

void loop()
{
    wire.tick();
    for (byte i = 0; i < 2; i++) {
        if (wire.rxs(i).buff_size() != 0) {
            byte val = wire.rxs(i).read();
            if (val == 0x0) {
                explode();
            }
            if (val == 0xf) {
                disarm();
            }
            if ((val & 0xc) == 0x80) {
                byte n = val & 0x3;
                lifes -= n;
                if (lifes < 0) {
                    lifes = 0;
                }
            }
        }
    }
    updateClock();
}
