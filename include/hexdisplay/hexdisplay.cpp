//
// Created by thepa on 17/03/2024.
//

#include "hexdisplay.h"
#include <TM1637Display.h>

void setupHexDisplay(tm1637* tm1637) {
    tm1637->init();
    tm1637->set(BRIGHT_TYPICAL);
}

void displayString(tm1637* tm1637, String str) {
    str.toUpperCase();
    tm1637->display(0, str.charAt(0));
    tm1637->display(1, str.charAt(1));
    tm1637->display(2, str.charAt(2));
    tm1637->display(3, str.charAt(3));
}