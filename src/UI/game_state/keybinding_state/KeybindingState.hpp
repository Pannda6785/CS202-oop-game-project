#ifndef KEYBINDING_STATE_HPP
#define KEYBINDING_STATE_HPP

#include "../GameState.hpp"
#include "../../button/ButtonManager.hpp"
#include "../main_menu_state/BehindDots.hpp"
#include "../state_heading/StateHeading.hpp"

class GameStateManager;

class KeybindingState : public GameState {
public:
    KeybindingState(GameStateManager& gsm, BehindDots &behindDots);
    ~KeybindingState();

    void enter() override;
    void update(float dt) override;
    void exit() override;
    void setVisible(bool visible);

private:
    GameStateManager& gameStateManager;
    ButtonManager buttonManager;
    BehindDots &behindDots;
    StateHeading heading;
    bool visible = true;
};

#endif // KEYBINDING_STATE_HPP