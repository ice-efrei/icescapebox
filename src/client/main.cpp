#include <Arduino.h>
#include "ICEscapeBox.h"

// #define TX 2
// #define RX 3


void setup()
{
    Serial.begin(9600);
    Serial.println("Waiting...");
    ieb.begin();
    Serial.print("Random seed is ");
    Serial.print(ieb.seed);
    Serial.print(", serial number is ");
    Serial.print(ieb.serialNumber);
    Serial.print(", ms is ");
    Serial.println(ieb.ms());
}

void loop()
{
    
}
