#include "passcodemg.h"
#include <TM1637Display.h>
#include <Keypad.h>
#include "hexdisplay/hexdisplay.h"

void setup_passcodemg(String* code_state, String* passcode, String* serial_number, int seed, tm1637* serial_display){
    *code_state = "";
    *passcode = generateCode(seed);
    *serial_number = generateSerialNumber(seed);
    displayString(serial_display, *serial_number);
}

void update_passcodemg(Keypad* keypad,tm1637* code_display, String* code_state, String* passcode, String* serial_number, int* completed){
    if(*completed == 1){
        displayString(code_display, passcode);
        return;
    }

    char key = keypad->getKey();
    if(key){
        *code_state += key;
        displayString(code_display, *code_state);
    }

    if(passcode == *code_state) *completed = 1;
    if(code_state->length() >= 4) *code_state = "";
}

String generateCode(int seed){
    return ""; // TODO: Implement passcode generation
}

String generateSerialNumber(int seed){
    return ""; // TODO: Implement serial number generation
}