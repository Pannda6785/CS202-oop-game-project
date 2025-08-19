#ifndef KEYBINDING_CONFIG_STATE_HPP
#define KEYBINDING_CONFIG_STATE_HPP

#include "../GameState.hpp"
#include "../../button/ButtonManager.hpp"
#include "../main_menu_state/BehindDots.hpp"
#include "../state_heading/StateHeading.hpp"
#include "KeybindDisplay.hpp"
#include <vector>

class GameStateManager;

class KeybindingConfigState : public GameState {
public:
    KeybindingConfigState(GameStateManager& gsm, BehindDots &behindDots, int playerIndex);
    ~KeybindingConfigState();

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
    std::vector<std::unique_ptr<KeybindDisplay>> keybindDisplays;
    std::vector<std::string> keybindActions;
    int playerIndex;
    bool isWaitingForKeyPressed = false;
    int pendingActionIndex = -1;

    int waitForKeyPress();
    void setInputKeyForAction(int actionIndex, int raylibKey);
    void updateDisplay();
};

#endif // KEYBINDING_CONFIG_STATE_HPP