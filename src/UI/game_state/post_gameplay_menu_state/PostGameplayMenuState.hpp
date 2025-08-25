#ifndef POST_GAMEPLAY_MENU_STATE_HPP
#define POST_GAMEPLAY_MENU_STATE_HPP

#include "../GameState.hpp"
#include "../../button/ButtonManager.hpp"
#include "../decorative_components/background/Background.hpp"
#include "../versus_mode_state/ribbon_effect/MovingTextTileManager.hpp"

class GameStateManager;

enum class PostGameOption {
    RESUME,
    RESTART,
    CHARACTER_SELECT,
    MAIN_MENU,
    NONE  // Default value
};

class PostGameplayMenuState : public GameState {
    friend class PostGameplayMenuStateBuilder;
public:
    PostGameplayMenuState(GameStateManager& gsm, PostGameOption &selectedOption);
    ~PostGameplayMenuState();

    void enter() override;
    void update(float dt) override;
    void exit() override;
    void setVisible(bool visible);
    
    // Get the selected option
    PostGameOption getSelectedOption() const;

private:
    GameStateManager& gameStateManager;
    ButtonManager buttonManager;
    Background background;
    bool visible = true;
    PostGameOption &selectedOption;
    MovingTextTileManager ribbonManager;
    PostGameOption choosingOption = PostGameOption::NONE;
    bool confirm = false;
    
    // Button configuration
    bool hasResumeButton = false;
    bool hasRestartButton = false;
    bool hasCharSelectButton = false;
    bool hasMainMenuButton = false;
    
    // Text for the ribbon
    std::string headerText = "GAME OVER";
    
    // Layout parameters
    int buttonWidth = GetScreenWidth();
    int buttonHeight = 80;
    int coordYFirstButton = 320;
    int buttonSpacing = 20;
    int offset = 50;
    int deltaOffset = -50;
    int fontSize = 75;
    
    // Add each type of button
    void addResumeButton(int& coordY, int& offsetX);
    void addRestartButton(int& coordY, int& offsetX);
    void addCharSelectButton(int& coordY, int& offsetX);
    void addMainMenuButton(int& coordY, int& offsetX);
};

#endif // POST_GAMEPLAY_MENU_STATE_HPP