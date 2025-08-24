#include "InputInterpreterManager.hpp"
#include "KeyboardInputInterpreter.hpp"
#include "ControllerInputInterpreter.hpp"
#include <raylib.h>
#include <iostream>

InputInterpreterManager& InputInterpreterManager::getInstance() {
    static InputInterpreterManager instance;
    return instance;
}

InputInterpreterManager::InputInterpreterManager() {
    for(int i = 0; i < 2; i++) interpreters.push_back(std::make_shared<KeyboardInputInterpreter>(i));
    for(int i = 0; i < 20; i++) interpreters.push_back(std::make_shared<ControllerInputInterpreter>());
}

InputInterpreterManager::~InputInterpreterManager() {
}

const std::vector<std::shared_ptr<InputInterpreter>> InputInterpreterManager::getInterpreters() const {
    return interpreters;
}

std::shared_ptr<InputInterpreter> InputInterpreterManager::getInterpreter(int playerIndex) {
    if (playerIndex < 0 || playerIndex >= interpreters.size()) {
        std::cerr << "Warning: Invalid player index " << playerIndex << std::endl;
        playerIndex = 0; // Default to first player
    }
    return interpreters[playerIndex];
}