#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "../../button/ButtonManager.hpp"
#include "../GameState.hpp"
#include "../../button/Button.hpp"
#include <memory>

class GameStateManager;

class MainMenuState : public GameState {
private:
    ButtonManager buttonManager;
    GameStateManager& gameStateManager;

public:
    MainMenuState(GameStateManager& gsm);
    ~MainMenuState();

    void enter() override;
    void update(float dt) override;
    void exit() override;
};

#endif // MAIN_MENU_STATE_HPP