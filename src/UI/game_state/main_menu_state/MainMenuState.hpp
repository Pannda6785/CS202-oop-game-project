#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "../../button/ButtonManager.hpp"
#include "../GameState.hpp"
#include "../../button/Button.hpp"
#include "../state_heading/StateHeading.hpp"
#include "ArtworkTitle.hpp"
#include "MovingTileGraphicsComponent.hpp"
#include "BehindDots.hpp"
#include <memory>

class GameStateManager;

class MainMenuState : public GameState {
private:
    ButtonManager buttonManager;
    GameStateManager& gameStateManager;
    ArtworkTitle artworkTitle;
    MovingTileGraphicsComponent movingTileEffect[2];
    BehindDots behindDots;
    StateHeading heading;
    bool isVisible = true;

    void setVisible(bool visible);

public:
    MainMenuState(GameStateManager& gsm);
    ~MainMenuState();

    void enter() override;
    void update(float dt) override;
    void exit() override;
};

#endif // MAIN_MENU_STATE_HPP