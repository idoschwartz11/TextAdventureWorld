#include <iostream>
#include <windows.h>
#include <conio.h>
#include "game.h"

using namespace std;

int main(int argc, char* argv[]) {
	game g;
	g.run_game(argc, argv);
	return 0;
}