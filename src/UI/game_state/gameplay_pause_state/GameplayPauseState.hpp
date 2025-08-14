#ifndef GAMEPLAY_PAUSE_STATE_HPP
#define GAMEPLAY_PAUSE_STATE_HPP

#include "../GameState.hpp"
#include "../../button/ButtonManager.hpp"
#include "../state_heading/StateHeading.hpp"

class GameStateManager;

enum class PauseMenuOption {
    RESUME,
    CHARACTER_SELECT,
    MAIN_MENU
};

class GameplayPauseState : public GameState {
public:
    GameplayPauseState(GameStateManager& gsm, PauseMenuOption& selectedOption);
    ~GameplayPauseState();

    void enter() override;
    void update(float dt) override;
    void exit() override;
    void setVisible(bool visible);

private:
    GameStateManager& gameStateManager;
    ButtonManager buttonManager;
    StateHeading heading;
    bool visible = true;
    PauseMenuOption &selectedOption;
};

#endif // GAMEPLAY_PAUSE_STATE_HPP