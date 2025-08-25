#ifndef CONFIRM_STATE_HPP
#define CONFIRM_STATE_HPP

#include "../../../graphics/GraphicsComponentManager.hpp"
#include "../GameState.hpp"
#include "../../button/ButtonManager.hpp"
#include "../main_menu_state/BehindDots.hpp"
#include "../state_heading/StateHeading.hpp"
#include <string>
#include <functional>

class GameStateManager;

class ConfirmState : public GameState {
public:
    ConfirmState(GameStateManager& gsm, bool& resultRef, 
                 const std::string& message = "are you sure?",
                 const std::string& yesText = "i'm sure",
                 const std::string& noText = "reconsider");
    ~ConfirmState();

    void enter() override;
    void update(float dt) override;
    void exit() override;
    void setVisible(bool visible);
    
    // Set custom callback for when user makes a choice
    void setOnConfirmCallback(std::function<void(bool)> callback);

private:
    GameStateManager& gameStateManager;
    ButtonManager buttonManager;
    StateHeading heading;
    bool& result;  // Reference to external boolean that will store the result
    bool visible = true;
    
    std::string confirmMessage;
    std::string yesButtonText;
    std::string noButtonText;
    
    std::function<void(bool)> onConfirmCallback;
    
    void setupButtons();
};

#endif // CONFIRM_STATE_HPP