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

}


