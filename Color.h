#pragma once
#include <windows.h>

enum class Color : WORD {
    BLACK = 0,
    BLUE = 1,   
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 14, 
    WHITE = 7
};


/*void setTextColor(Color color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(color));
}*/