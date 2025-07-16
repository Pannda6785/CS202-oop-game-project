#ifndef GAME_STATE_MANAGER_HPP
#define GAME_STATE_MANAGER_HPP

#include <memory>
#include "GameState.hpp"

class GameStateManager {
public:
    GameStateManager();
    ~GameStateManager();

    // State operations (deferred)
    void changeState(std::unique_ptr<GameState> state);

    // Main loop delegation
    void update(float dt);

    // Access current state
    GameState* getCurrentState();

    // Check if state is empty
    bool isEmpty() const;

    // Call this at the end of your main loop to apply any pending state changes
    void processPendingStateChanges();

private:
    std::unique_ptr<GameState> currentState = nullptr;

    // Deferred state change mechanism
    bool hasPendingState = false;
    std::unique_ptr<GameState> pendingState = nullptr;

    void applyPendingAction();
};

#endif // GAME_STATE_MANAGER_HPP