#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib> // for rand()

struct Riddle {
    std::string question;
    std::string answer;
    std::string clue;
};

class RiddleManager {
    std::vector<Riddle> riddles;

public:
    void loadRiddles(const std::string& filename);

    int getRandomRiddleIndex() const {
        if (riddles.empty()) return -1;
        return rand() % riddles.size();
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

    // Check if the answer provided matches (logic for later)
    bool checkAnswer(int index, const std::string& input) const {
        if (index >= 0 && index < riddles.size()) {
            return riddles[index].answer == input;
        }
        return false;
    }
};