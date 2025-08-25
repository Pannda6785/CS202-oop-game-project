#ifndef GRAPHIC_OPTIONS_HPP
#define GRAPHIC_OPTIONS_HPP

#include "../../GameState.hpp"
#include "../../../button/ButtonManager.hpp"
#include "../../main_menu_state/BehindDots.hpp"
#include "../../state_heading/StateHeading.hpp"

class GameStateManager;

class GraphicOptions : public GameState {
public:
    GraphicOptions(GameStateManager& gsm, BehindDots &behindDots);
    ~GraphicOptions();

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
    
    // Helper methods to update buttons to reflect current settings
    void updateButtonStates();
    void setResolution(int width, int height);
    void setFullscreen(bool enable);
    
    // Buttons
    int windowedButtonIndex = -1;
    int fullscreenButtonIndex = -1;
};

#endif // GRAPHIC_OPTIONS_HPP