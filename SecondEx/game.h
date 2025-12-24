#pragma once
#include "Player.h"
#include "Screen.h"
#include "Point.h"
#include "Color.h"
#include "Obstacle.h"
#include <vector>

class game {
private:
	bool game_is_running = true;
	bool pause = false;
	bool colors = true; // will be toggled in menu
	bool p1_ready_to_transition = false;
	bool p2_ready_to_transition = false;

	vector<Obstacle> obstacles;
	void loadObstaclesFromScreen(Screen& screen);
	void renderFrame(Screen& screen, Player players[]);

	Screen screens[4]; // total number of screens - room 0,secret room,room 1, room 2
	int current_screen = 0;
	int darkRoomIndex = 1;

	// players
	Player player1;
	Player player2;

	// colors
	Color player1_color = Color::GREEN;
	Color player2_color = Color::BLUE;

	int current_game_cycle = 0;

	int findObstacleIndexAt(int x, int y) const;


public:
	game()
		: player1(Point(10, 10, 1, 0, '$'), '$', "WDAXS", screens[current_screen]),
		player2(Point(15, 5, 0, 1, '&'), '&', "ILJMK", screens[current_screen])
	{
		player1.setOther(&player2);
		player2.setOther(&player1);
	}
	bool isObstacleAt(int x, int y) const;
	bool tryPushObstacle(Screen& screen, Player& p, Player& other, Direction dir, int pBonusPower = 0);

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
	void bomb_explode(int bombX, int bombY, Screen& screen, Player players[]);
	void updateBomb(Screen& screen, Player players[]);
	void activateBomb(int x, int y);


	//room travel
	void setPlayerReady(char playerChar);
	bool isPlayerReady(char playerChar) const;


	//colors
	Color get_player_color(char playerChar) const;
	bool getColorsState() const { return colors; }
};