#pragma once
#include "InputController.h"
#include <fstream>
#include <conio.h>
#include <iostream>

class KeyboardRecorder : public InputController {
private:
    std::ofstream stepsFile;
    bool isSaving;

public:
    KeyboardRecorder(unsigned int seed, bool saveMode) : isSaving(saveMode) {
        if (isSaving) {
            stepsFile.open("adv-world.steps", std::ios::out | std::ios::trunc);
            if (stepsFile.is_open()) {
                stepsFile << seed << std::endl;
            }
            else {
                std::cerr << "Error: Could not create adv-world.steps" << std::endl;
            }
        }
    }

    ~KeyboardRecorder() {
        if (stepsFile.is_open()) {
            stepsFile.close();
        }
    }

    bool hasInput(int currentCycle, char& key) override {
        if (_kbhit()) {
            key = _getch();
            if (isSaving && stepsFile.is_open()) {
                stepsFile << currentCycle << " " << key << std::endl;
            }
            return true;
        }
        return false;
    }
};