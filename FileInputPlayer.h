#pragma once
#include "InputController.h"
#include <fstream>
#include <vector>
#include <utility>
#include <string>

// Reads keys from "adv-world.steps" in the SAME format that KeyboardRecorder writes:
class FileInputPlayer : public InputController {
private:
    unsigned int seed = 0;
    std::vector<std::pair<int, char>> steps;
    size_t index = 0;

public:
    unsigned int getSeed() const { return seed; }
    explicit FileInputPlayer(const std::string& stepsFile); 
    bool hasInput(int currentCycle, char& key) override;
};
