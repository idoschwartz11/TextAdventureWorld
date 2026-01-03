#include <iostream>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <vector>
#include "Screen.h"
#include "utils.h"
#include "game.h"
#include "Player.h"

// --- HUD Logic (User 1's Dynamic Implementation compliant with Ex2) ---

std::string Screen::fitToHudWidth(std::string s) {
    if ((int)s.size() > HUD_W) 
		s.resize(HUD_W);
    if ((int)s.size() < HUD_W) 
		s.append(HUD_W - (int)s.size(), ' ');
    return s;
}

void Screen::writeHudLine(int rowOffset, const std::string& text) {
    const std::string line = fitToHudWidth(text);
    const int y = legendRow + rowOffset;
    if (y < 0 || y >= MAX_Y) return;
    for (int i = 0; i < HUD_W; ++i) {
        const int x = legendCol + i;
        if (x < 0 || x >= MAX_X) continue;
        screen[y][x] = line[i];
    }
}

void Screen::rebuildHud() {
	char buf[128];

	std::snprintf(buf, sizeof(buf), "$:%02dx%02d Inv:%c <3:%d |",
		hudP1x, hudP1y,
		(hudP1Inv == 0 ? ' ' : hudP1Inv),
		hudP1Hearts);
	writeHudLine(0, buf);

	std::snprintf(buf, sizeof(buf), "-SCORE:%03d----C:%02d-|",
		hudScore, hudCoins);
	writeHudLine(1, buf);

	std::snprintf(buf, sizeof(buf), "&:%02dx%02d Inv:%c <3:%d |",
		hudP2x, hudP2y,
		(hudP2Inv == 0 ? ' ' : hudP2Inv),
		hudP2Hearts);
	writeHudLine(2, buf);
}

Screen::Screen() {};

void Screen::setMap(const std::string map[MAX_Y]) {
	for (int i = 0; i < MAX_Y; ++i) {
		screen[i] = map[i];

		if ((int)screen[i].size() < MAX_X) {
			screen[i].append(MAX_X - (int)screen[i].size(), ' ');
		}
	}
}

// User 1's File Loading (Crucial for Ex2)
bool Screen::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return false;

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(line);
    }

    if ((int)lines.size() < MAX_Y) lines.resize(MAX_Y, std::string());
    if ((int)lines.size() > MAX_Y) lines.resize(MAX_Y);

    for (auto& l : lines) {
        if ((int)l.size() < MAX_X) l.append(MAX_X - (int)l.size(), ' ');
        if ((int)l.size() > MAX_X) l.resize(MAX_X);
    }

    // Default placement if L is missing
    legendRow = 0;
    legendCol = 0;

    for (int y = 0; y < MAX_Y; ++y) {
        screen[y] = lines[y];
        for (int x = 0; x < MAX_X; ++x) {
            if (screen[y][x] == 'L') {
                legendRow = y;
                legendCol = x;
                screen[y][x] = ' '; // remove anchor from map
            }
        }
    }

    rebuildHud();
    return true;
}

// --- Drawing and Setting Chars ---

void Screen::draw() const {
	cls();
	gotoxy(0, 0);
	for (size_t i = 0; i < MAX_Y - 1; ++i) {
		std::cout << screen[i] << std::endl;
	}
	std::cout << screen[MAX_Y - 1];
	std::cout.flush();
}

void Screen::setCharAt(int x, int y, char c) {
	if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y) {
		return; 
	}
	screen[y][x] = c;
    
    // Only draw immediately if it's NOT in the HUD area (to prevent flickering or partial updates)
    // or if we really want real-time updates.
    // Generally safe to draw:
	gotoxy(x, y);
    
    // We need to determine color for this specific char update
    Color color;
    if (c == '$' || c == '&') 
		color = get_player_color(c);
	else if ((x == 14 && y == 0) || (x == 15 && y == 0) ||
		(x == 14 && y == 2) || (x == 15 && y == 2)) {
		color = Color::RED;
	}
    else
		color = get_object_color(x, y, c);
    
    set_text_color(color);
	std::cout << c;
    set_text_color(Color::WHITE);
}

// --- Data Setters (Merged: User 2's split data feeding User 1's HUD) ---

void Screen::setCoins(int totalCoins) {
	if (totalCoins < 0) totalCoins = 0;
	if (totalCoins > 99) totalCoins = 99;
	hudCoins = totalCoins;
	rebuildHud();
}


void Screen::setScore(int score) {
    if (score < 0) score = 0;
    if (score > 999) score = 999;
    hudScore = score;
    rebuildHud();
}

void Screen::setP1Hearts(int hearts) {
    if (hearts < 0) hearts = 0;
    if (hearts > 9) hearts = 9;
    hudP1Hearts = hearts;
    rebuildHud();
}

void Screen::setP2Hearts(int hearts) {
    if (hearts < 0) hearts = 0;
    if (hearts > 9) hearts = 9;
    hudP2Hearts = hearts;
    rebuildHud();
}

void Screen::setP1Position(int px, int py) {
	hudP1x = (std::max)(0, (std::min)(99, px));
	hudP1y = (std::max)(0, (std::min)(99, py));
	rebuildHud();
}

void Screen::setP2Position(int px, int py) {
	hudP2x = (std::max)(0, (std::min)(99, px));
	hudP2y = (std::max)(0, (std::min)(99, py));
	rebuildHud();
}

void Screen::setP1Inventory(char c) {
    hudP1Inv = c;
    rebuildHud();
}

void Screen::setP2Inventory(char c) {
    hudP2Inv = c;
    rebuildHud();
}

// --- Game Logic Interactions (Merged) ---

void Screen::activateBomb(int x, int y) {
	if (activeGame != nullptr) {
		setCharAt(x, y, '@');
		activeGame->activateBomb(x, y);
	}
}

// Merged Door Transition: Supports User 2's destination char logic
void Screen::playerReadyToTransition(char playerChar, char destChar) {
	if (activeGame != nullptr) {
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

// --- Visibility and Rendering ---

bool Screen::isInHud(int x, int y) const {
    // User 1's dynamic HUD check
	const bool isFrame = (x == 0) || (y == 0) || (x == MAX_X - 1) || (y == MAX_Y - 1);
	const bool isHudRect = (x >= legendCol && x < legendCol + HUD_W &&
	                        y >= legendRow && y < legendRow + HUD_H);
	return isFrame || isHudRect;
}

bool Screen::isVisibleFromPlayer(int x, int y, const Player& p) const {
	int radius = (p.getItem() == '!') ? 5 : 2; 
	int px = p.getX();
	int py = p.getY();
	int dx = std::abs(x - px);
	int dy = std::abs(y - py);
	int dist = (dx > dy ? dx : dy);
	return dist <= radius;
}

bool Screen::isCellVisible(int x, int y, const Player& p1, const Player& p2) const {
	if (isInHud(x, y)) return true;
	if (isVisibleFromPlayer(x, y, p1)) return true;
	if (isVisibleFromPlayer(x, y, p2)) return true;
	return false;
}

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
				if (activeGame != nullptr && activeGame->isObstacleAt(x, y))
					c = '*';
				if (isP1)      c = '$';
				else if (isP2) c = '&';
			}
			drawCharAt(x, y, c);
		}
	}
	std::cout.flush();
}

void Screen::renderFull(const Player& p1, const Player& p2) {
	for (int y = 0; y < MAX_Y; ++y) {
		for (int x = 0; x < MAX_X; ++x) {
			Point p(x, y, ' ');
			char c = getCharAt(p);
			bool isP1 = (x == p1.getX() && y == p1.getY());
			bool isP2 = (x == p2.getX() && y == p2.getY());

			if (activeGame != nullptr && activeGame->isObstacleAt(x, y))
				c = '*';

			if (isP1)      c = '$';
			else if (isP2) c = '&';

			drawCharAt(x, y, c);
		}
	}
	std::cout.flush();
}

// --- Colors and Special Features (Merged User 2) ---

bool Screen::is_heart_char(int x, int y, char c) const {
    // Merged: Check if inside dynamic HUD rect
    if (c != '<' && c != '3') return false;
    const bool inHudRect = (x >= legendCol && x < legendCol + HUD_W &&
                            y >= legendRow && y < legendRow + HUD_H);
    return inHudRect;
}

Color Screen::get_object_color(int x, int y, char c) const {
	if (activeGame == nullptr || !activeGame->getColorsState()) {
		return Color::WHITE;
	}

    // User 2's extended logic
	if (c == 'H' && activeGame->isShopHeart(x, y)) {
		return Color::RED;
	}

	bool isDoorChar = (c == '1' || c == '2' || c == '9');
    // Note: User 2 checked x < 70, but now HUD is dynamic. 
    // We assume anything that isn't HUD is part of the map.
	if (isDoorUnlocked(x, y) && isdigit(c)) return Color::GREEN;

	switch (c) {
	case '@': return Color::BLUE;    // Bomb
	case 'K': return Color::DARK_YELLOW;  // Key
	case '!': return Color::DARK_RED;     // Torch
	case 'W': return Color::DARK_GRAY; // wall
	case '#': return Color::DARK_MAGENTA; // spring
	case 'o': return Color::YELLOW; // coin
	case '?': return Color::MAGENTA; // clue
	case 'H': return Color::WHITE; // hearts in shop
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
	else if ((x == 14 && y == 0) || (x == 15 && y == 0) ||
		(x == 14 && y == 2) || (x == 15 && y == 2)) {
		color = Color::RED;
	}
	else {
		color = get_object_color(x, y, c);
	}

	set_text_color(color);
	gotoxy(x, y);
	std::cout << c;
	// set_text_color(Color::WHITE); // Optimization: don't reset immediately to avoid flicker
}

// --- Shop & Riddles (User 2) ---

bool Screen::is_shop_item(char c) const {
	return (c == '!' || c == 'K' || c == 'H' || c == '?');
}


std::string Screen::getGameClue() const {
	if (activeGame) {
		return activeGame->getCurrentClue();
	}
	return "No active game.";
}

void Screen::displayMessage(const std::string& msg) {
    // Print message at bottom of screen or safe area
	gotoxy(2, 23); 
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

std::vector<std::string> Screen::getMapState() const {
	std::vector<std::string> currentState;
	for (int i = 0; i < MAX_Y; ++i) {
		std::string row = screen[i];
		for (char& c : row) { //ignoring players..
			if (c == '$' || c == '&') {
				c = ' ';
			}
		}
		currentState.push_back(row);
	}
	return currentState;
}

void Screen::setMapFromState(const std::vector<std::string>& mapState) {
	for (int i = 0; i < MAX_Y && i < (int)mapState.size(); ++i) {
		screen[i] = mapState[i];
	}
	rebuildHud();
}


void Screen::setDoorUnlocked(int x, int y) {
	if (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y) {
		unlockedDoors[y][x] = true;
	}
}

bool Screen::isDoorUnlocked(int x, int y) const {
	if (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y) {
		return unlockedDoors[y][x];
	}
	return false;
}

void Screen::resetUnlockedDoors() {
	for (int y = 0; y < MAX_Y; ++y) {
		for (int x = 0; x < MAX_X; ++x) {
			unlockedDoors[y][x] = false;
		}
	}
}