#pragma once
#include "InputController.h"
#include <fstream>
#include <conio.h>
#include <iostream>

class KeyboardRecorder : public InputController {
private:
    std::ofstream stepsFile;
    bool isSaving;
    bool inRiddleMode = false;

    bool isRelevantKey(char key) {
        const std::string relevant = "WADXSEIJLMKOwadxseijlmko1";
        if (key == 27) return true; // ESC
        return relevant.find(key) != std::string::npos;
    }

public:
    KeyboardRecorder(unsigned int seed, bool saveMode) : isSaving(saveMode) {
        if (isSaving) {
            stepsFile.open("adv-world.steps", std::ios::out | std::ios::trunc);
            if (stepsFile.is_open()) stepsFile << seed << std::endl;
        }
    }

    ~KeyboardRecorder() {
        if (stepsFile.is_open()) stepsFile.close();
    }

    void setRiddleMode(bool mode) override {
        inRiddleMode = mode;
    }

    bool hasInput(int currentCycle, char& key) override {
        if (_kbhit()) {
            key = _getch();

            if (!inRiddleMode && !isRelevantKey(key)) {
                return false;
            }

            if (isSaving && stepsFile.is_open()) {
                char keyToSave = key;

                if (key == 13 || key == 10) {
                    keyToSave = '1';
                }
                

                stepsFile << currentCycle << " " << keyToSave << std::endl;
            }
            return true;
        }
        return false;
    }
};