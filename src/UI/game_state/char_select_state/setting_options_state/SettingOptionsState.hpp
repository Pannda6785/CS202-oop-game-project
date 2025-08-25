#ifndef SETTING_OPTIONS_STATE_HPP
#define SETTING_OPTIONS_STATE_HPP

#include "../../GameState.hpp"
#include "../../../button/ButtonManager.hpp"
#include "../../main_menu_state/BehindDots.hpp"
#include "../../state_heading/StateHeading.hpp"
#include "../../../../graphics/GraphicsComponentManager.hpp"
#include "../../decorative_components/background/Background.hpp"

class GameStateManager;
class WorldBuilder;

class SettingOptionsState : public GameState {
public:
    SettingOptionsState(GameStateManager& gsm, WorldBuilder& worldBuilder);
    ~SettingOptionsState();

    void enter() override;
    void update(float dt) override;
    void exit() override;
    void setVisible(bool visible);

private:
    GameStateManager& gameStateManager;
    ButtonManager buttonManager;
    WorldBuilder& worldBuilder;
    Background background;
    bool visible = true;
    
    // Settings variables
    int stockCount = 3;
    std::vector<std::string> availableChallenges;
    
    // Update button text based on current settings
    void updateButtonLabels();
};

#endif // SETTING_OPTIONS_STATE_HPP