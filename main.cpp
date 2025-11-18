#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Player.h"
#include "Screen.h"
#include "utils.h"
#include "game.h"

using namespace std;
enum Keys { ESC = 27 };

int main() {
	game g;
	g.run_game();
/*
	int hearts = 3;

	hideCursor();
	Screen screen;
	screen.draw();

	Point p1(10, 10, 1, 0, '$');
	Point p2(15, 5, 1, 0, '&');

	Player players[] = {
		Player(p1, '$', "WADXS", screen),
		Player(p2, '&', "IJLMK", screen),
	};

	players[0].setOther(&players[1]);
	players[1].setOther(&players[0]);

	players[0].draw();
	players[1].draw();

	while (true) {
		players[0].move();
		players[1].move();
		if (_kbhit()) {
			char key = _getch();
			if (key == Keys::ESC) {
				// Pause - till any key is pressed
				key = _getch();
				if (key == 'H' || key == 'h') {
					break;
				}
			}
			else {
				players[0].handleKeyPressed(key);
				players[1].handleKeyPressed(key);
			}
		}
		Sleep(85);
	}
	cls();
	*/
}


