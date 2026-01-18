#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib> 
#include <algorithm>

struct Riddle {
    std::string question;
    std::string answer;
    std::string clue;
};

class RiddleManager {
    std::vector<Riddle> riddles;
    std::vector<bool> usedFlags;

public:
    void loadRiddles(const std::string& filename);

    int getRandomRiddleIndex() {
        if (riddles.empty()) return -1;

        bool allUsed = true;
        for (bool u : usedFlags) {
            if (!u) {
                allUsed = false;
                break;
            }
        }

        if (allUsed) {
            std::fill(usedFlags.begin(), usedFlags.end(), false);
        }

        int idx;
        do {
            idx = rand() % riddles.size();
        } while (usedFlags[idx] == true);

        usedFlags[idx] = true;
        return idx;
    }

    std::string getClue(int index) const {
        if (index >= 0 && index < riddles.size()) {
            return riddles[index].clue;
        }
        return "No clue available.";
    }

    std::string getQuestion(int index) const {
        if (index >= 0 && index < riddles.size()) {
            return riddles[index].question;
        }
        return "No question available.";
    }

    bool checkAnswer(int index, const std::string& input) const {
        if (index >= 0 && index < riddles.size()) {
            return riddles[index].answer == input;
        }
        return false;
    }
};