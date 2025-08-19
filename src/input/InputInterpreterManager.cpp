#include "InputInterpreterManager.hpp"
#include <raylib.h>
#include <iostream>

InputInterpreterManager& InputInterpreterManager::getInstance() {
    static InputInterpreterManager instance;
    return instance;
}

InputInterpreterManager::InputInterpreterManager() {
    // Set up default key mappings
    setupDefaultKeyMappings();
    
    // Initialize interpreters for default number of players
    interpreters.reserve(DEFAULT_PLAYERS);
    for (int i = 0; i < DEFAULT_PLAYERS; ++i) {
        setupPlayerWithDefaultControls(i);
    }
}

InputInterpreterManager::~InputInterpreterManager() {
    // No cleanup needed as vectors and unique_ptr will handle it
}

void InputInterpreterManager::setupDefaultKeyMappings() {
    // Resize the vector to hold mappings for default number of players
    defaultKeyMappings.resize(DEFAULT_PLAYERS);
    currentKeyMappings.resize(DEFAULT_PLAYERS);
    
    // Each player needs NUM_INPUTS key mappings
    for (int i = 0; i < DEFAULT_PLAYERS; i++) {
        defaultKeyMappings[i].resize(Unit::NUM_INPUTS);
        currentKeyMappings[i].resize(Unit::NUM_INPUTS);
    }

    // Player 1 default mappings (Arrow keys + Z,X,C,V)
    defaultKeyMappings[0][static_cast<int>(Unit::Input::MoveUp)] = KEY_UP;
    defaultKeyMappings[0][static_cast<int>(Unit::Input::MoveDown)] = KEY_DOWN;
    defaultKeyMappings[0][static_cast<int>(Unit::Input::MoveLeft)] = KEY_LEFT;
    defaultKeyMappings[0][static_cast<int>(Unit::Input::MoveRight)] = KEY_RIGHT;
    defaultKeyMappings[0][static_cast<int>(Unit::Input::Basic)] = KEY_Z;
    defaultKeyMappings[0][static_cast<int>(Unit::Input::Wide)] = KEY_X;
    defaultKeyMappings[0][static_cast<int>(Unit::Input::Offensive)] = KEY_C;
    defaultKeyMappings[0][static_cast<int>(Unit::Input::Defensive)] = KEY_V;
    defaultKeyMappings[0][static_cast<int>(Unit::Input::Focus)] = KEY_LEFT_SHIFT;
    defaultKeyMappings[0][static_cast<int>(Unit::Input::Toggle)] = KEY_LEFT_CONTROL;
    defaultKeyMappings[0][static_cast<int>(Unit::Input::Pause)] = KEY_ESCAPE;
    defaultKeyMappings[0][static_cast<int>(Unit::Input::Confirm)] = KEY_ENTER;
    defaultKeyMappings[0][static_cast<int>(Unit::Input::Back)] = KEY_BACKSPACE;

    // Player 2 default mappings (WASD + J,K,L,;)
    defaultKeyMappings[1][static_cast<int>(Unit::Input::MoveUp)] = KEY_W;
    defaultKeyMappings[1][static_cast<int>(Unit::Input::MoveDown)] = KEY_S;
    defaultKeyMappings[1][static_cast<int>(Unit::Input::MoveLeft)] = KEY_A;
    defaultKeyMappings[1][static_cast<int>(Unit::Input::MoveRight)] = KEY_D;
    defaultKeyMappings[1][static_cast<int>(Unit::Input::Basic)] = KEY_J;
    defaultKeyMappings[1][static_cast<int>(Unit::Input::Wide)] = KEY_K;
    defaultKeyMappings[1][static_cast<int>(Unit::Input::Offensive)] = KEY_L;
    defaultKeyMappings[1][static_cast<int>(Unit::Input::Defensive)] = KEY_SEMICOLON;
    defaultKeyMappings[1][static_cast<int>(Unit::Input::Focus)] = KEY_RIGHT_SHIFT;
    defaultKeyMappings[1][static_cast<int>(Unit::Input::Toggle)] = KEY_RIGHT_CONTROL;
    defaultKeyMappings[1][static_cast<int>(Unit::Input::Pause)] = KEY_ESCAPE;
    defaultKeyMappings[1][static_cast<int>(Unit::Input::Confirm)] = KEY_RIGHT_SHIFT;
    defaultKeyMappings[1][static_cast<int>(Unit::Input::Back)] = KEY_BACKSPACE;

    currentKeyMappings = defaultKeyMappings;
}

void InputInterpreterManager::setupPlayerWithDefaultControls(int playerIndex) {
    // Create a new keyboard interpreter
    auto interpreter = std::make_unique<KeyboardInputInterpreter>();
    
    // Apply default key mappings for this player
    for (int j = 0; j < Unit::NUM_INPUTS; ++j) {
        interpreter->setKeyMapping(static_cast<Unit::Input>(j), defaultKeyMappings[playerIndex][j]);
    }
    
    // Add to the vector of interpreters
    interpreters.push_back(std::move(interpreter));
}

int InputInterpreterManager::getPlayerCount() const {
    return interpreters.size();
}

void InputInterpreterManager::addPlayer() {
    int newPlayerIndex = interpreters.size();
    
    // If we don't have default mappings for this player, add them
    // (This uses player 2 settings as a template for any additional players)
    if (newPlayerIndex >= defaultKeyMappings.size()) {
        defaultKeyMappings.push_back(defaultKeyMappings[1]); // Clone player 2 mappings
    }
    
    // Set up the new player
    setupPlayerWithDefaultControls(newPlayerIndex);
}

InputInterpreter* InputInterpreterManager::getInterpreter(int playerIndex) {
    if (playerIndex < 0 || playerIndex >= interpreters.size()) {
        std::cerr << "Warning: Invalid player index " << playerIndex << std::endl;
        playerIndex = 0; // Default to first player
    }
    return interpreters[playerIndex].get();
}

KeyboardInputInterpreter* InputInterpreterManager::getKeyboardInterpreter(int playerIndex) {
    if (playerIndex < 0 || playerIndex >= interpreters.size()) {
        std::cerr << "Warning: Invalid player index " << playerIndex << std::endl;
        playerIndex = 0; // Default to first player
    }
    return interpreters[playerIndex].get();
}

void InputInterpreterManager::setKeyMapping(int playerIndex, Unit::Input input, int raylibKey) {
    if (playerIndex < 0 || playerIndex >= interpreters.size()) {
        std::cerr << "Warning: Invalid player index for key mapping" << std::endl;
        return;
    }
    // Update current key mapping
    currentKeyMappings[playerIndex][static_cast<int>(input)] = raylibKey;
    interpreters[playerIndex]->setKeyMapping(input, raylibKey);
}

void InputInterpreterManager::resetKeyMappings(int playerIndex) {
    if (playerIndex < 0 || playerIndex >= interpreters.size() || 
        playerIndex >= defaultKeyMappings.size()) {
        std::cerr << "Warning: Invalid player index for key reset" << std::endl;
        return;
    }
    currentKeyMappings[playerIndex] = defaultKeyMappings[playerIndex];
    for (int j = 0; j < Unit::NUM_INPUTS; ++j) {
        interpreters[playerIndex]->setKeyMapping(
            static_cast<Unit::Input>(j), 
            defaultKeyMappings[playerIndex][j]
        );
    }
}

void InputInterpreterManager::update(float dt) {
    for (auto& interpreter : interpreters) {
        interpreter->update(dt);
    }
}

int InputInterpreterManager::getKeyMapping(int playerIndex, Unit::Input input) {
    if (playerIndex < 0 || playerIndex >= interpreters.size()) {
        std::cerr << "Warning: Invalid player index for key mapping" << std::endl;
        return -1; // Invalid key mapping
    }
    return currentKeyMappings[playerIndex][static_cast<int>(input)];
}

Unit::Vec2D InputInterpreterManager::getMovement(int playerIndex) const {
    if (playerIndex < 0 || playerIndex >= interpreters.size()) {
        std::cerr << "Warning: Invalid player index for movement" << std::endl;
        return Unit::Vec2D(0, 0);
    }
    
    return interpreters[playerIndex]->getMovement();
}

bool InputInterpreterManager::isInputPressed(int playerIndex, Unit::Input input) const {
    if (playerIndex < 0 || playerIndex >= interpreters.size()) {
        std::cerr << "Warning: Invalid player index for input check" << std::endl;
        return false;
    }
    
    return interpreters[playerIndex]->isInputPressed(input);
}

bool InputInterpreterManager::isInputReleased(int playerIndex, Unit::Input input) const {
    if (playerIndex < 0 || playerIndex >= interpreters.size()) {
        std::cerr << "Warning: Invalid player index for input check" << std::endl;
        return false;
    }
    
    return interpreters[playerIndex]->isInputReleased(input);
}

bool InputInterpreterManager::isInputDown(int playerIndex, Unit::Input input) const {
    if (playerIndex < 0 || playerIndex >= interpreters.size()) {
        std::cerr << "Warning: Invalid player index for input check" << std::endl;
        return false;
    }
    
    return interpreters[playerIndex]->isInputDown(input);
}

bool InputInterpreterManager::isInputUp(int playerIndex, Unit::Input input) const {
    if (playerIndex < 0 || playerIndex >= interpreters.size()) {
        std::cerr << "Warning: Invalid player index for input check" << std::endl;
        return false;
    }
    
    return interpreters[playerIndex]->isInputUp(input);
}

bool InputInterpreterManager::isInputPressed(Unit::Input input) const{
    for (const auto& interpreter : interpreters) {
        if (interpreter->isInputPressed(input)) {
            return true;
        }
    }
    return false;
}

bool InputInterpreterManager::isInputReleased(Unit::Input input) const {
    for (const auto& interpreter : interpreters) {
        if (interpreter->isInputReleased(input)) {
            return true;
        }
    }
    return false;
}

bool InputInterpreterManager::isInputDown(Unit::Input input) const {
    for (const auto& interpreter : interpreters) {
        if (interpreter->isInputDown(input)) {
            return true;
        }
    }
    return false;
}

bool InputInterpreterManager::isInputUp(Unit::Input input) const {
    for (const auto& interpreter : interpreters) {
        if (interpreter->isInputUp(input)) {
            return true;
        }
    }
    return false;
}