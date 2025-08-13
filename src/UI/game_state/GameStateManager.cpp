#include "GameStateManager.hpp"
#include "main_menu_state/MainMenuState.hpp"
#include "solo_mode_state/SoloModeState.hpp"
#include "versus_mode_state/versus_player_state/VersusPlayerState.hpp"

GameStateManager::GameStateManager() : currentAction(StateAction::None) {
    // Initialize the game state manager with the main menu state
    changeState(std::make_unique<MainMenuState>(*this));
    // changeState(std::make_unique<VersusPlayerState>(*this, "Sun Priestess", "Silent Redhood"));
}

GameStateManager::~GameStateManager() = default;

void GameStateManager::changeState(std::unique_ptr<GameState> state) {
    currentAction = StateAction::ChangeState;
    pendingState = std::move(state);
}

void GameStateManager::pushState(std::unique_ptr<GameState> state) {
    currentAction = StateAction::PushState;
    pendingState = std::move(state);
}

void GameStateManager::popState() {
    currentAction = StateAction::PopState;
}

void GameStateManager::changeCurrentState(std::unique_ptr<GameState> state) {
    currentAction = StateAction::ChangeCurrentState;
    pendingState = std::move(state);
}

void GameStateManager::update(float dt) {
    if(!stateStack.empty()){
        stateStack.top()->update(dt);
    }
}

GameState* GameStateManager::getCurrentState() {
    return stateStack.empty() ? nullptr : stateStack.top().get();
}

bool GameStateManager::isEmpty() const {
    return stateStack.empty();
}

void GameStateManager::processPendingStateChanges() {
    switch(currentAction) {
        case StateAction::ChangeState:
            applyChangeState();
            break;
        case StateAction::PushState:
            applyPushState();
            break;
        case StateAction::PopState:
            applyPopState();
            break;
        case StateAction::ChangeCurrentState:
            applyChangeCurrentState();
            break;
        default:
            break;
    }
    currentAction = StateAction::None;
}

void GameStateManager::applyChangeState(){
    while(!stateStack.empty()) stateStack.pop();
    stateStack.push(std::move(pendingState));
}

void GameStateManager::applyPushState(){
    stateStack.push(std::move(pendingState));
}

void GameStateManager::applyPopState(){
    if(!stateStack.empty()) stateStack.pop();
}

void GameStateManager::applyChangeCurrentState() {
    if (!stateStack.empty()) {
        stateStack.pop();  // Remove current state
        stateStack.push(std::move(pendingState));  // Add new state
    } else {
        // If stack is empty, behave like changeState
        stateStack.push(std::move(pendingState));
    }
}