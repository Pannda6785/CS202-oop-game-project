// #include "GameStateManager.hpp"

// GameStateManager::GameStateManager(){
//     while(!states.empty()) {
//         states.pop();
//     }
//     pendingAction = PendingAction::None;
//     pendingState = nullptr;
// }
// GameStateManager::~GameStateManager() = default;

// void GameStateManager::pushState(std::unique_ptr<GameState> state) {
//     pendingAction = PendingAction::Push;
//     pendingState = std::move(state);
// }

// void GameStateManager::popState() {
//     pendingAction = PendingAction::Pop;
//     pendingState = nullptr;
// }

// void GameStateManager::changeState(std::unique_ptr<GameState> state) {
//     // pendingAction = PendingAction::Change;
//     // pendingState = std::move(state);
//     states.push(std::move(state));
// }

// void GameStateManager::update(float dt) {
//     if (!states.empty() && states.top()) {
//         states.top()->update(dt);
//     }
// }

// GameState* GameStateManager::getCurrentState() {
//     return states.empty() ? nullptr : states.top().get();
// }

// bool GameStateManager::isEmpty() const {
//     return states.empty();
// }

// void GameStateManager::processPendingStateChanges() {
//     applyPendingAction();
// }

// void GameStateManager::applyPendingAction() {
//     switch (pendingAction) {
//         case PendingAction::Push:
//             if (pendingState) {
//                 states.push(std::move(pendingState));
//             }
//             break;
//         case PendingAction::Pop:
//             if (!states.empty()) {
//                 states.pop();
//             }
//             break;
//         case PendingAction::Change:
//             while (!states.empty()) {
//                 states.pop();
//             }
//             if (pendingState) {
//                 states.push(std::move(pendingState));
//             }
//             break;
//         case PendingAction::None:
//         default:
//             break;
//     }
//     pendingAction = PendingAction::None;
//     pendingState = nullptr;
// }

#include "GameStateManager.hpp"

GameStateManager::GameStateManager() : hasPendingState(false), currentState(nullptr), pendingState(nullptr) {}
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