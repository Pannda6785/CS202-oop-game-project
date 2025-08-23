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
    for(int i = 0; i < 20; i++) interpreters.push_back(std::make_unique<KeyboardInputInterpreter>(i));
    for(int i = 0; i < 20; i++) interpreters.push_back(std::make_unique<ControllerInputInterpreter>());
}

InputInterpreterManager::~InputInterpreterManager() {
}

std::vector<const InputInterpreter*> InputInterpreterManager::getInterpreters() const {
    std::vector<const InputInterpreter*> result;
    for (const auto& interpreter : interpreters) {
        result.push_back(interpreter.get());
    }
    return result;
}

InputInterpreter* InputInterpreterManager::getInterpreter(int playerIndex) {
    if (playerIndex < 0 || playerIndex >= interpreters.size()) {
        std::cerr << "Warning: Invalid player index " << playerIndex << std::endl;
        playerIndex = 0; // Default to first player
    }
    return interpreters[playerIndex].get();
}