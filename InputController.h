#pragma once

class InputController {
public:
    virtual ~InputController() {}
    virtual bool hasInput(int currentCycle, char& key) = 0;
};