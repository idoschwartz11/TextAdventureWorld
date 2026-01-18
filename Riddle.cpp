#include "Riddle.h"

void RiddleManager::loadRiddles(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open riddles file!" << std::endl;
        return;
    }

    riddles.clear();

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> parts;

        while (std::getline(ss, segment, '|')) {
            parts.push_back(segment);
        }

        if (parts.size() >= 3) {
            Riddle r;
            r.question = parts[0];
            r.answer = parts[1];
            r.clue = parts[2];
            riddles.push_back(r);
        }
    }
    file.close();
    usedFlags.assign(riddles.size(), false);
}