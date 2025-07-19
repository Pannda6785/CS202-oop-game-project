#include "GameStateManager.hpp"
#include "main_menu_state/MainMenuState.hpp"

GameStateManager::GameStateManager() : currentAction(StateAction::None) {
    // Initialize the game state manager with the main menu state
    changeState(std::make_unique<MainMenuState>(*this));
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