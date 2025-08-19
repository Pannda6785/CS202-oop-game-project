#ifndef GAMEPLAY_PAUSE_STATE_HPP
#define GAMEPLAY_PAUSE_STATE_HPP

#include "../GameState.hpp"
#include "../../button/ButtonManager.hpp"
#include "../decorative_components/Background.hpp"
#include "../decorative_components/MovingTextTile.hpp"
#include "../versus_mode_state/ribbon_effect/MovingTextTileManager.hpp"

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
    Background background;
    bool visible = true;
    PauseMenuOption &selectedOption;
    MovingTextTileManager ribbonManager;
    PauseMenuOption choosingOption;
    bool confirm = false;
};

#endif // GAMEPLAY_PAUSE_STATE_HPP