#ifndef OPTIONS_STATE_HPP
#define OPTIONS_STATE_HPP

#include "../GameState.hpp"
#include "../../button/ButtonManager.hpp"
#include "../main_menu_state/BehindDots.hpp"
#include "../state_heading/StateHeading.hpp"
#include "../../../graphics/GraphicsComponentManager.hpp"

class GameStateManager;

class OptionsState : public GameState {
public:
    OptionsState(GameStateManager& gsm, BehindDots &behindDots);
    ~OptionsState();

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

#endif // OPTIONS_STATE_HPP