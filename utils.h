#pragma once

enum KeyCodes { // constant for keys
    KEY_ESC = 27,
    KEY_ENTER = 13,
    KEY_BACKSPACE = 8,
    KEY_ONE = '1'
};


void gotoxy(int x, int y);
void hideCursor();
void cls();
