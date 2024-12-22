#ifndef PASSCODEMG_H
#define PASSCODEMG_H
#include <TM1637Display.h>

void setupPasscode(Keypad* keypad, tm1637* code_display, tm1637* serial_display, String* code_state, String* passcode, String* serial_number, int* completed);
void updatePasscode(Keypad* keypad, tm1637* code_display, String* code_state, String* passcode, int* completed);
String generateCode(int seed);
String generateSerialCode(int seed);

#endif //PASSCODEMG_H