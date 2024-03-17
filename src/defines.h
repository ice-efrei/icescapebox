#ifndef DEFINES_H
#define DEFINES_H

const byte ROWS = 4;
const byte COLS = 4;
const byte rowPins[ROWS] = {29, 27, 25, 23};
const byte colPins[COLS] = {37, 35, 33, 31};

const char KEYPAD_INPUTS[ROWS][COLS] = {
    {'1','2','3','F'},
    {'4','5','6','E'},
    {'7','8','9','D'},
    {'A','0','B','C'}
};

const int KEYPAD_CLK = 2;
const int KEYPAD_DIO = 3;

const int SERIAL_CLK = 4;
const int SERIAL_DIO = 5;

#endif //DEFINES_H
