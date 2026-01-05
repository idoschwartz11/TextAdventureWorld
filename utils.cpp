#include <iostream>
#include <windows.h> 
#include <cstdlib>

#include "utils.h"

void gotoxy(int x, int y) {
    std::cout.flush();
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE; // Visibility set to FALSE
    SetConsoleCursorInfo(consoleHandle, &info);
}

void cls() {
    system("cls");
}
