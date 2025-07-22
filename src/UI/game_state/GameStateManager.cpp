#include "GameStateManager.hpp"
#include "main_menu_state/MainMenuState.hpp"
#include "solo_mode_state/SoloModeState.hpp"

GameStateManager::GameStateManager() : hasPendingState(false), currentState(nullptr), pendingState(nullptr) {
    // Initialize the game state manager with the main menu state
    changeState(std::make_unique<SoloModeState>(*this));
}

GameStateManager::~GameStateManager() = default;

void GameStateManager::changeState(std::unique_ptr<GameState> state) {
    hasPendingState = true;
    pendingState = std::move(state);
}

void GameStateManager::update(float dt) {
    if (currentState) {
        currentState->update(dt);
    }
}

GameState* GameStateManager::getCurrentState() {
    return currentState.get();
}

bool GameStateManager::isEmpty() const {
    return !currentState;
}

void GameStateManager::processPendingStateChanges() {
    applyPendingAction();
}

void GameStateManager::applyPendingAction() {
    if (hasPendingState) {
        currentState = std::move(pendingState);
        hasPendingState =  false;
    }
}