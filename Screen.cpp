#include <iostream>
#include "Screen.h"
#include "utils.h"
#include "game.h"
#include "Player.h"

Screen::Screen() {};

void Screen::setMap(const std::string map[MAX_Y]) {
	for (int i = 0; i < MAX_Y; ++i) {
		screen[i] = map[i];
	}
}


static void setTwoDigitNumberAt(Screen& scr, int x, int y, int value) {
	if (value < 0) value = 0;
	if (value > 99) value = 99;
	int tens = value / 10;
	int ones = value % 10;
	scr.setCharAt(x, y, '0' + tens);
	scr.setCharAt(x + 1, y, '0' + ones);
}



void Screen::draw() const {
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
}

void Screen::setP1Coins(int coins) {
	if (coins < 0) coins = 0;
	if (coins > 99) coins = 99;

	int tens = coins / 10;
	int ones = coins % 10;

	setCharAt(76, 3, '0' + tens);
	setCharAt(77, 3, '0' + ones);
}

void Screen::setP2Coins(int coins) {
	if (coins < 0) coins = 0;
	if (coins > 99) coins = 99;

	int tens = coins / 10;
	int ones = coins % 10;

	setCharAt(76, 14, '0' + tens);
	setCharAt(77, 14, '0' + ones);
}

void Screen::setP1Hearts(int hearts) {
	if (hearts < 0) hearts = 0;
	if (hearts > 9) hearts = 9; 

	setCharAt(76, 2, '0' + hearts);
}

void Screen::setP2Hearts(int hearts) {
	if (hearts < 0) hearts = 0;
	if (hearts > 9) hearts = 9;

	setCharAt(76, 13, '0' + hearts);
}


void Screen::setP1Position(int px, int py) {
	setTwoDigitNumberAt(*this, 75, 8, px);
	setTwoDigitNumberAt(*this, 75, 9, py);
}

void Screen::setP2Position(int px, int py) {
	setTwoDigitNumberAt(*this, 75, 20, px);
	setTwoDigitNumberAt(*this, 75, 21, py);
}

void Screen::set_score(int score) {
	if (score < 0) score = 0;
	if (score > 9999) score = 999;

	//int thousands = score / 1000;
	int hundreds = (score / 100) % 10;
	int tens = (score / 10) % 10;
	int ones = score % 10;

	//(73, 23, '0' + thousands); 
	setCharAt(73, 23, '0' + hundreds);  
	setCharAt(74, 23, '0' + tens);     
	setCharAt(75, 23, '0' + ones);  
}

void Screen::activateBomb(int x, int y) {
	if (activeGame != nullptr) {
		setCharAt(x, y, '@');
		activeGame->activateBomb(x, y);
	}
}





//door
void Screen::playerReadyToTransition(char playerChar, char destChar) {
	if (activeGame != nullptr) {
		// Pass the destination character to the game object
		activeGame->setPlayerReady(playerChar, destChar);
	}
}

bool Screen::isOtherPlayerReady(char playerChar) const {
	if (activeGame != nullptr) {
		char otherChar = (playerChar == '$' ? '&' : '$');
		return activeGame->isPlayerReady(otherChar);
	}
	return false;
}

//HUD always visible
bool Screen::isInHud(int x, int y) const {
	bool isInHudRow = (x >= 69) || (x <= 0) || (y <= 0) || (y >= 24);
	return isInHudRow;
	//return x >= 70;
}

// is cell (x,y) visible from player p?
bool Screen::isVisibleFromPlayer(int x, int y, const Player& p) const {
	int radius = (p.getItem() == '!') ? 5 : 2; //radius 2 or 5

	int px = p.getX();
	int py = p.getY();

	int dx = std::abs(x - px);
	int dy = std::abs(y - py);

	int dist = (dx > dy ? dx : dy);

	return dist <= radius;
}

// is cell (x,y) visible to at least one player?
bool Screen::isCellVisible(int x, int y, const Player& p1, const Player& p2) const {
	if (isInHud(x, y))
		return true;

	if (isVisibleFromPlayer(x, y, p1))
		return true;
	if (isVisibleFromPlayer(x, y, p2))
		return true;

	return false;
}

// render map with visibility from both players
void Screen::renderWithVisibility(const Player& p1, const Player& p2) {
	for (int y = 0; y < MAX_Y; ++y) {
		for (int x = 0; x < MAX_X; ++x) {

			Point p(x, y, ' ');
			char c = getCharAt(p);

			bool isP1 = (x == p1.getX() && y == p1.getY());
			bool isP2 = (x == p2.getX() && y == p2.getY());

			bool visible = isCellVisible(x, y, p1, p2);

			if (!visible && !isInHud(x, y)) {
				c = ' ';
			}
			else {
				if (isP1)      c = '$';
				else if (isP2) c = '&';
			}
			drawCharAt(x, y, c);
		}
	}
}

void Screen::renderFull(const Player& p1, const Player& p2) {
	for (int y = 0; y < MAX_Y; ++y) {
		for (int x = 0; x < MAX_X; ++x) {
			Point p(x, y, ' ');
			char c = getCharAt(p);

			bool isP1 = (x == p1.getX() && y == p1.getY());
			bool isP2 = (x == p2.getX() && y == p2.getY());

			if (isP1)      c = '$';
			else if (isP2) c = '&';

			drawCharAt(x, y, c);
		}
	}
}

// colors
bool Screen::is_heart_char(int x, int y, char c) const {
	// 1. Check if the character is one of the two static symbols.
	if (c != '<' && c != '3') {
		return false;
	}

	// 2. Check Player 1 static heart symbol coordinates: (71, 2) and (72, 2)
	if ((x == 73 && y == 2) || (x == 72 && y == 2)) {
		return true;
	}

	// 3. Check Player 2 static heart symbol coordinates: (71, 13) and (72, 13)
	if ((x == 73 && y == 13) || (x == 72 && y == 13)) {
		return true;
	}


	return false;
}



Color Screen::get_object_color(int x, int y, char c) const {
	if (activeGame == nullptr || !activeGame->getColorsState()) {
		return Color::WHITE;
	}

	if (c == 'H' && activeGame->isShopHeart(x, y)) {
		return Color::RED;
	}

	bool isDoorChar = (c == '1' || c == '2' || c == '9');

	if (isDoorChar && x < 70) {
		bool isTemporarilyUnlocked = activeGame->isDoorUnlocked(x, y);
		return isTemporarilyUnlocked ? Color::GREEN : Color::RED;
	}
	switch (c) {
	case '@': return Color::BLUE;    // Bomb
	case 'K': return Color::DARK_YELLOW;  // Key
	case '!': return Color::DARK_RED;     // Torch
	case 'W': return Color::DARK_GRAY; // wall
	case '#': return Color::DARK_MAGENTA; // spring
	case 'o': return Color::YELLOW; // coin
	case '?': return Color::MAGENTA; // clue
	case 'H': return Color::WHITE; //hearts in shop
	case '\\': return Color::GREEN; // ON
	case '/':  return Color::RED; // OFF


	default:  return Color::WHITE;
	}
}


Color Screen::get_player_color(char playerChar) const {
	if (activeGame == nullptr) return Color::WHITE;
	return activeGame->get_player_color(playerChar);
}

void Screen::set_text_color(Color color) {
	if (activeGame != nullptr) {
		activeGame->set_text_color(color);
	}
}

void Screen::drawCharAt(int x, int y, char c) {
	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y) {
		return;
	}
	Color color;

	if (c == '$' || c == '&') {
		color = get_player_color(c);
	}
	else if (is_heart_char(x, y, c)) {
		color = Color::RED;
	}
	else {
		color = get_object_color(x, y, c);
	}

	set_text_color(color);

	gotoxy(x, y);
	std::cout << c;

	set_text_color(Color::WHITE);
}


//shop
bool Screen::is_shop_item(char c) const {
	return (c == '!' || c == 'K' || c == 'H' || c == '?');
	//torch key health clue
}

void Screen::setDoorUnlocked(int x, int y) {
	if (activeGame != nullptr) {
		activeGame->setDoorUnlocked(x, y);
	}
}

//riddels
std::string Screen::getGameClue() const {
	if (activeGame) {
		return activeGame->getCurrentClue();
	}
	return "No active game.";
}

void Screen::displayMessage(const std::string& msg) {
	gotoxy(10, 16);
	set_text_color(Color::CYAN);
	std::cout << "CLUE: " << msg << "   ";
	set_text_color(Color::WHITE);
}

bool Screen::triggerRiddle() {
	if (activeGame) {
		return activeGame->handle_riddle_encounter();
	}
	return false;
}

