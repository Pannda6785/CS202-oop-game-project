#ifndef GAME_STATE_MANAGER_HPP
#define GAME_STATE_MANAGER_HPP

#include <memory>
#include <stack>
#include "GameState.hpp"

class GameStateManager {
public:
    GameStateManager();
    ~GameStateManager();

    // State operations (deferred)
    void changeState(std::unique_ptr<GameState> state);
    void pushState(std::unique_ptr<GameState> state);
    void popState();
    void changeCurrentState(std::unique_ptr<GameState> state); // Added new function

    // Main loop delegation
    void update(float dt);

    // Access current state
    GameState* getCurrentState();

    // Check if state is empty
    bool isEmpty() const;

    // Call this at the end of your main loop to apply any pending state changes
    void processPendingStateChanges();

private:
    std::stack<std::unique_ptr<GameState>> stateStack;
    
    // Deferred state change mechanism
    enum class StateAction {
        ChangeState,
        PushState,
        PopState,
        ChangeCurrentState, // Added new action
        None
    };
    StateAction currentAction = StateAction::None;
    std::unique_ptr<GameState> pendingState = nullptr;

    void applyChangeState();
    void applyPushState();
    void applyPopState();
    void applyChangeCurrentState(); // Added new apply function
};

#endif // GAME_STATE_MANAGER_HPP