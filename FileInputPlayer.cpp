#include "FileInputPlayer.h"

FileInputPlayer::FileInputPlayer(const std::string& stepsFile) {
    std::ifstream in(stepsFile);
    if (!in.is_open()) {
        // If file is missing, keep steps empty (game will run with no input).
        return;
    }
    in >> seed;
    int cycle;
    char key;
	while (in >> cycle >> key) { // Read until EOF
        // Ignore ESC in load mode (requirement: no user input, even ESC)
        if (key == 27) continue;
        steps.push_back({ cycle, key });
    }
}

bool FileInputPlayer::hasInput(int currentCycle, char& key)  {
    if (index < steps.size() && steps[index].first == currentCycle) {
        key = steps[index].second;
        index++;
        return true;
    }
    return false;
}