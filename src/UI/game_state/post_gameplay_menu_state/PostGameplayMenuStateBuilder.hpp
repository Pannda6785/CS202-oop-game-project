#ifndef POST_GAMEPLAY_MENU_STATE_BUILDER_HPP
#define POST_GAMEPLAY_MENU_STATE_BUILDER_HPP

#include "PostGameplayMenuState.hpp"
#include <memory>

class PostGameplayMenuStateBuilder {
public:
    PostGameplayMenuStateBuilder(GameStateManager& gsm, PostGameOption& selectedOption);
    
    // Button visibility
    PostGameplayMenuStateBuilder& setResumeButton();
    PostGameplayMenuStateBuilder& setRestartButton();
    PostGameplayMenuStateBuilder& setCharSelectButton();
    PostGameplayMenuStateBuilder& setMainMenuButton();
    
    // Text configuration
    PostGameplayMenuStateBuilder& setHeaderText(const std::string& text);
    
    // Layout customization
    PostGameplayMenuStateBuilder& setButtonHeight(int height);
    PostGameplayMenuStateBuilder& setInitialY(int y);
    PostGameplayMenuStateBuilder& setButtonSpacing(int spacing);
    PostGameplayMenuStateBuilder& setOffset(int offset);
    PostGameplayMenuStateBuilder& setDeltaOffset(int delta);
    PostGameplayMenuStateBuilder& setFontSize(int size);
    
    // Build the state
    std::unique_ptr<PostGameplayMenuState> build();
    
private:
    std::unique_ptr<PostGameplayMenuState> state;
};

#endif // POST_GAMEPLAY_MENU_STATE_BUILDER_HPP