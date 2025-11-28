#pragma once
#include "Player.h"
#include "Screen.h"
#include "Point.h"
#include "Color.h"


class game {
private:
	bool game_is_running = true;
	bool pause = false;
	bool colors = true; // will be toggled in menu


	Screen screens[8]; // total number of screens
	int current_screen = 0;

	// players
	Player player1;
	Player player2;

	// colors
	Color player1_color = Color::GREEN;
	Color player2_color = Color::BLUE;

	int current_game_cycle = 0;


public:

	game()
		: player1(Point(10, 10, 1, 0, '$'), '$', "WDAXS", screens[current_screen]),
		player2(Point(15, 5, 0, 1, '&'), '&', "ILJMK", screens[current_screen])
	{
		player1.setOther(&player2);
		player2.setOther(&player1);
	}


	void run_game(); // entry point
	void main_menu();
	void start_new_game(); // starts a new game;
	void show_instructions(); // show instructions screen

	void game_loop(Screen& screen, Player players[]); // main game loop

	void pause_screen(); // draw pause screen
	bool handle_pause();

	void set_text_color(Color color);

	//bomb state
	bool bombActive = false;
	int activeBombX = -1;
	int activeBombY = -1;
	int bombTimer = 0; // The 5 game cycle
	void bomb_explode(int bombX, int bombY, Screen& screen);
	void updateBomb(Screen& screen);
	void activateBomb(int x, int y);


};