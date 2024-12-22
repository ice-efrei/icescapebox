#include <Arduino.h>
#include <Keypad.h>
#include "passcode/defines.h"
#include "passcode/hexdisplay.h"
#include "passcode/passcodemg.h"
#include <TM1637Display.h>

TM1637Display code_display(KEYPAD_CLK, KEYPAD_DIO);
TM1637Display serial_display(SERIAL_CLK, SERIAL_DIO);

Keypad passcode_keypad = Keypad(makeKeymap(KEYPAD_INPUTS), (byte*) rowPins, (byte*) colPins, ROWS, COLS);

String code_state, passcode, serial_number;
int completed = 0, seed = 1234;

void setup() {
    setupHexDisplay(&code_display);
    setupHexDisplay(&serial_display);

    code_state = "";
    passcode = generateCode(seed);
    serial_number = generateSerialCode(seed);
    displayString(&serial_display, serial_number);
}

void loop() {
    if(completed == 1){
        displayString(&code_display, passcode);
        return;
    }

    char key = passcode_keypad.getKey();
    if(key){
        code_state += key;
        displayString(&code_display, code_state);
    }

    if(passcode == code_state) completed = 1;
    if(code_state.length() >= 4) code_state = "";
}