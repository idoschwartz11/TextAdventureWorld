#pragma once
#include "Player.h"
#include "Screen.h"
#include "Point.h"
#include "Color.h"
#include "Riddle.h"

class game {
private:
	bool game_is_running = true;
	bool pause = false;
	bool colors = true; // will be toggled in menu
	bool p1_ready_to_transition = false;
	bool p2_ready_to_transition = false;
	int p1_dest_room = -1;
	int p2_dest_room = -1;
	int unlockedDoorX = -1;
	int unlockedDoorY = -1;

	Screen screens[4]; // total number of screens - room 0,secret room,room 1, room 2
	int current_screen = 0;
	int darkRoomIndex = 1;

	// riddles
	RiddleManager riddle_manager;
	int last_riddle_index = -1;  // <--- 2. Declare this here!

	// players
	Player player1;
	Player player2;

	// colors
	Color player1_color = Color::GREEN;
	Color player2_color = Color::BLUE;
	
	//bomb
	int current_game_cycle = 0;


	//score
	int score = 1000;
	int game_cycle_counter = 0;

	

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
	void bomb_explode(int bombX, int bombY, Screen& screen, Player players[]);
	void updateBomb(Screen& screen, Player players[]);
	void activateBomb(int x, int y);


	//room travel
	void setPlayerReady(char playerChar, char destChar);
	bool isPlayerReady(char playerChar) const;
	bool isDoorUnlocked(int x, int y) const;
	void setDoorUnlocked(int x, int y);
	void clearUnlockedDoor();


	//colors
	Color get_player_color(char playerChar) const;
	bool getColorsState() const { return colors; }
	Color get_object_color(int x, int y, char c) const;

	//score
	void updateScore(Screen& screen);

	bool isShopHeart(int x, int y) const;


	//riddle
	bool handle_riddle_encounter();
	std::string getCurrentClue() const;

	//switch
	void check_switches(Screen& screen);
};