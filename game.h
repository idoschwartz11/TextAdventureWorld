#pragma once
#include "Player.h"
#include "Screen.h"
#include "Point.h"
#include "Color.h"
#include "Obstacle.h" // User 1 feature
#include "Riddle.h"   // User 2 feature
#include <vector>
#include <string>

class game {
private:
	bool game_is_running = true;
	bool pause = false;
	bool colors = true; // toggled in menu
	
	// Transition State
	bool p1_ready_to_transition = false;
	bool p2_ready_to_transition = false;
	int p1_dest_room = -1; // User 2: specific room destination
	int p2_dest_room = -1;
	
	// Doors (User 2)
	int unlockedDoorX = -1;
	int unlockedDoorY = -1;

	// Obstacles (User 1)
	std::vector<Obstacle> obstacles;
	void loadObstaclesFromScreen(Screen& screen);
	void renderFrame(Screen& screen, Player players[]);
	int findObstacleIndexAt(int x, int y) const;

	Screen screens[4]; // room 0, secret room, room 1, room 2
	int current_screen = 0;
	int darkRoomIndex = 1;

	// Riddles (User 2)
	RiddleManager riddle_manager;
	int last_riddle_index = -1;

	// Players
	Player player1;
	Player player2;

	// Colors
	Color player1_color = Color::GREEN;
	Color player2_color = Color::BLUE;

	// Score & Time (User 2)
	int score = 1000;
	int game_cycle_counter = 0;
	int current_game_cycle = 0;

public:
	game()
		: player1(Point(10, 10, 1, 0, '$'), '$', "WDAXS", screens[current_screen]),
		player2(Point(15, 5, 0, 1, '&'), '&', "ILJMK", screens[current_screen])
	{
		player1.setOther(&player2);
		player2.setOther(&player1);
	}

	// --- Obstacles Logic (User 1) ---
	bool isObstacleAt(int x, int y) const;
	bool tryPushObstacle(Screen& screen, Player& p, Player& other, Direction dir, int pBonusPower = 0);

	// --- Core Game Flow ---
	void run_game(); 
	void main_menu();
	void start_new_game(); 
	void show_instructions(); 
	void game_loop(Screen& screen, Player players[]); 

	// --- Pause & Utils ---
	void pause_screen(); 
	bool handle_pause();
	void set_text_color(Color color);

	// --- Bomb State ---
	bool bombActive = false;
	int activeBombX = -1;
	int activeBombY = -1;
	int bombTimer = 0; 
	void bomb_explode(int bombX, int bombY, Screen& screen, Player players[]);
	void updateBomb(Screen& screen, Player players[]);
	void activateBomb(int x, int y);

	// --- Room Travel & Doors (Merged) ---
	// Updated to accept destination char (User 2 requirement)
	void setPlayerReady(char playerChar, char destChar);
	bool isPlayerReady(char playerChar) const;
	
	// Door locking helpers (User 2)
	bool isDoorUnlocked(int x, int y) const;
	void setDoorUnlocked(int x, int y);
	void clearUnlockedDoor();

	// --- Colors ---
	Color get_player_color(char playerChar) const;
	bool getColorsState() const { return colors; }
	// Note: get_object_color is handled in Screen.cpp logic using isShopHeart below

	// --- Score & Shop (User 2) ---
	void updateScore(Screen& screen);
	bool isShopHeart(int x, int y) const;

	// --- Riddles (User 2) ---
	bool handle_riddle_encounter();
	std::string getCurrentClue() const;

	// --- Switches (User 2) ---
	void check_switches(Screen& screen);
};