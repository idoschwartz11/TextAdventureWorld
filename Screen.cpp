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
	// òãëåï äîôä äìåâéú
	screen[y][x] = c;
	// òãëåï òì äîñê ø÷ ùì äúà äæä
	gotoxy(x, y);
	cout << c;
	cout.flush();
}
void Screen::setP1Coins(int coins) {
	if (coins < 0) coins = 0;
	if (coins > 99) coins = 99;

	int tens = coins / 10;
	int ones = coins % 10;

	// שורה 3, עמודות 76–77 (x00 של P.I)
	setCharAt(76, 3, '0' + tens);
	setCharAt(77, 3, '0' + ones);
}

void Screen::setP2Coins(int coins) {
	if (coins < 0) coins = 0;
	if (coins > 99) coins = 99;

	int tens = coins / 10;
	int ones = coins % 10;

	// שורה 14, עמודות 76–77 (x00 של P.II)
	setCharAt(76, 14, '0' + tens);
	setCharAt(77, 14, '0' + ones);
}

void Screen::setP1Hearts(int hearts) {
	if (hearts < 0) hearts = 0;
	if (hearts > 9) hearts = 9; // ספרה אחת

	// בשורה 2, עמודה 76 – שם נמצאת הספרה של x3 ב-| <3 x3  |
	setCharAt(76, 2, '0' + hearts);
}

void Screen::setP2Hearts(int hearts) {
	if (hearts < 0) hearts = 0;
	if (hearts > 9) hearts = 9;

	// בשורה 13, עמודה 76 – הספרה של x3 ב-| <3 x3  | של P.II
	setCharAt(76, 13, '0' + hearts);
}


void Screen::setP1Position(int px, int py) {
	// X ùì ùç÷ï I – ùåøä 8, òîåãåú 75–76
	setTwoDigitNumberAt(*this, 75, 8, px);
	// Y ùì ùç÷ï I – ùåøä 9, òîåãåú 75–76
	setTwoDigitNumberAt(*this, 75, 9, py);
}

void Screen::setP2Position(int px, int py) {
	// X ùì ùç÷ï II – ùåøä 20, òîåãåú 75–76
	setTwoDigitNumberAt(*this, 75, 20, px);
	// Y ùì ùç÷ï II – ùåøä 21, òîåãåú 75–76
	setTwoDigitNumberAt(*this, 75, 21, py);
}

void Screen::activateBomb(int x, int y) {
	if (activeGame != nullptr) {
		setCharAt(x, y, '@');
		activeGame->activateBomb(x, y);
	}
}


//door
void Screen::playerReadyToTransition(char playerChar) {
	if (activeGame != nullptr) {
		activeGame->setPlayerReady(playerChar);
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
	bool isInHudRow = (x >= 69) || (x <= 1) || (y <= 1) || (y >= 23);
	return isInHudRow;
	//return x >= 70;
}

// is cell (x,y) visible from player p?
bool Screen::isVisibleFromPlayer(int x, int y, const Player& p) const {
	int radius = (p.getItem() == '!') ? 8 : 3; //radius 3 or 8

	int px = p.getX();
	int py = p.getY();

	int dx = std::abs(x - px);
	int dy = std::abs(y - py);

	int dist = (dx > dy ? dx : dy);

	return dist <= radius;
}

// is cell (x,y) visible to at least one player?
bool Screen::isCellVisible(int x, int y, const Player& p1, const Player& p2) const {
	// HUD úîéã âìåé
	if (isInHud(x, y))
		return true;

	// úà âìåé àí ìôçåú àçã îäùç÷ðéí øåàä àåúå
	if (isVisibleFromPlayer(x, y, p1))
		return true;
	if (isVisibleFromPlayer(x, y, p2))
		return true;

	return false;
}

// render map with visibility from both players
void Screen::renderWithVisibility(const Player& p1, const Player& p2) {
	for (int y = 0; y < MAX_Y; ++y) {
		gotoxy(0, y);
		for (int x = 0; x < MAX_X; ++x) {

			// áøéøú îçãì: îä ùéù áîôä
			Point p(x, y, ' ');
			char c = getCharAt(p);

			bool isP1 = (x == p1.getX() && y == p1.getY());
			bool isP2 = (x == p2.getX() && y == p2.getY());

			bool visible = isCellVisible(x, y, p1, p2);

			if (!visible && !isInHud(x, y)) {
				// çåùê – ìà øåàéí ëìåí áîùáöú äæàú
				c = ' ';
			}
			else {
				// àí øåàéí – äùç÷ðéí òöîí âåáøéí òì îä ùéù áîôä
				if (isP1)      c = '$';
				else if (isP2) c = '&';
			}

			cout << c;
		}
	}
}

void Screen::renderFull(const Player& p1, const Player& p2) {
	for (int y = 0; y < MAX_Y; ++y) {
		gotoxy(0, y);
		for (int x = 0; x < MAX_X; ++x) {
			Point p(x, y, ' ');
			char c = getCharAt(p);

			bool isP1 = (x == p1.getX() && y == p1.getY());
			bool isP2 = (x == p2.getX() && y == p2.getY());

			if (isP1)      c = '$';
			else if (isP2) c = '&';

			cout << c;
		}
	}
}
