#include <iostream>
#include "Screen.h"
#include "utils.h"

static void setTwoDigitNumberAt(Screen& scr, int x, int y, int value) {
	if (value < 0) value = 0;
	if (value > 99) value = 99;
	int tens = value / 10;
	int ones = value % 10;
	scr.setCharAt(x, y, '0' + tens);
	scr.setCharAt(x + 1, y, '0' + ones);
}



void Screen::draw()  {
	cls();
	gotoxy(0, 0);
	for (size_t i = 0; i < MAX_Y - 1; ++i) {
		cout << screen[i] << endl;
	}
	cout << screen[MAX_Y - 1];
	cout.flush();
}

void Screen::setCharAt(int x, int y, char c) {
	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y) {
		return; // Out of bounds
	}
	screen[y][x] = c;
	gotoxy(x, y);
	cout << c;
	cout.flush();
}
void Screen::setP1Coins(int coins) {
   if (coins < 0) coins = 0;
   if (coins > 99) coins = 99; // Two digits

   int tens = coins / 10;
   int ones = coins % 10;

   Screen screenInstance; // Create an instance of Screen
   screenInstance.setCharAt(76, 3, '0' + tens);
   screenInstance.setCharAt(77, 3, '0' + ones);
}

void Screen::setP2Coins(int coins) {
	if (coins < 0) coins = 0;
	if (coins > 99) coins = 99;

	int tens = coins / 10;
	int ones = coins % 10;

	Screen screenInstance; // Create an instance of Screen
	screenInstance.setCharAt(76, 14, '0' + tens);
	screenInstance.setCharAt(77, 14, '0' + ones);
}


void Screen::setP1Position(int px, int py) {
	setTwoDigitNumberAt(*this, 75, 8, px);
	setTwoDigitNumberAt(*this, 75, 9, py);
}

void Screen::setP2Position(int px, int py) {
	setTwoDigitNumberAt(*this, 75, 20, px);
	setTwoDigitNumberAt(*this, 75, 21, py);
}
