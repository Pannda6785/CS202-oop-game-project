#ifndef INPUT_INTERPRETER_MANAGER_HPP
#define INPUT_INTERPRETER_MANAGER_HPP

#include "InputInterpreter.hpp"
#include "KeyboardInputInterpreter.hpp"
#include <vector>
#include <memory>

class InputInterpreterManager {
public:
    // Singleton access method
    static InputInterpreterManager& getInstance();
    
    // Interpreter access
    InputInterpreter* getInterpreter(int playerIndex);
    KeyboardInputInterpreter* getKeyboardInterpreter(int playerIndex);
    
    // Player management
    int getPlayerCount() const;
    void addPlayer(); // Dynamically add a player with default controls
    
    // Key mapping modification
    void setKeyMapping(int playerIndex, Unit::Input input, int raylibKey);
    void resetKeyMappings(int playerIndex);
    
    // Update all interpreters
    void update(float dt);
    int getKeyMapping(int playerIndex, Unit::Input input);
    
    // Convenience input forwarding methods
    Unit::Vec2D getMovement(int playerIndex) const;
    bool isInputPressed(int playerIndex, Unit::Input input) const;
    bool isInputReleased(int playerIndex, Unit::Input input) const;
    bool isInputDown(int playerIndex, Unit::Input input) const;
    bool isInputUp(int playerIndex, Unit::Input input) const;

    bool isInputPressed(Unit::Input input) const;
    bool isInputReleased(Unit::Input input) const;
    bool isInputDown(Unit::Input input) const;
    bool isInputUp(Unit::Input input) const;
    
    // Constants
    static const int DEFAULT_PLAYERS = 2;

private:
    // Singleton implementation
    InputInterpreterManager();
    ~InputInterpreterManager();
    InputInterpreterManager(const InputInterpreterManager&) = delete;
    InputInterpreterManager& operator=(const InputInterpreterManager&) = delete;
    
    // Default key mappings
    void setupDefaultKeyMappings();
    void setupPlayerWithDefaultControls(int playerIndex);
    
    // Player input interpreters - using vector for flexibility
    std::vector<std::unique_ptr<KeyboardInputInterpreter>> interpreters;
    
    // Default key mappings for each player - using vector for flexibility
    std::vector<std::vector<int>> defaultKeyMappings;
    std::vector<std::vector<int>> currentKeyMappings;
};

#endif // INPUT_INTERPRETER_MANAGER_HPP