#include <Arduino.h>
#include "defines.h"
#include <Keypad.h>
#include "hexdisplay/hexdisplay.h"
#include "passcodemg/passcodemg.h"
#include <TM1637Display.h>

TM1637Display code_display(KEYPAD_CLK, KEYPAD_DIO);
TM1637Display serial_display(SERIAL_CLK, SERIAL_DIO);

Keypad passcode_keypad = Keypad(makeKeymap(KEYPAD_INPUTS), (byte*) rowPins, (byte*) colPins, ROWS, COLS);

String code_state, passcode, serial_number;
int completed = 0, seed = 1234;


void setup() {
    setupHexDisplay(&code_display);
    setupHexDisplay(&serial_display);

    setupPasscode(&passcode_keypad, &code_display, &serial_display, &code_state, &passcode, &serial_number, &completed);
}

void loop() {
    updatePasscode(&passcode_keypad, &code_display, &code_state, &passcode, &completed);
}