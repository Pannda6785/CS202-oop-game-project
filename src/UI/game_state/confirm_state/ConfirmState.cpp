#include "ConfirmState.hpp"
#include "../GameStateManager.hpp"
#include "../../../audio/AudioManager.hpp"
#include <iostream>

ConfirmState::ConfirmState(GameStateManager &gameStateManager, bool& resultRef, 
                           const std::string& message,
                           const std::string& yesText, 
                           const std::string& noText)
    : gameStateManager(gameStateManager), 
      result(resultRef),
      confirmMessage(message),
      yesButtonText(yesText),
      noButtonText(noText),
      onConfirmCallback(nullptr) {
    enter();
}

ConfirmState::~ConfirmState() {
    exit();
}

void ConfirmState::enter() {
    
    // Set up the heading
    int headingPosY = GraphicsComponentManager::NATIVE_HEIGHT / 3;
    int fontSize = 75;
    int dividerLineLength = 600;
    int dividerLineThickness = 3;
    int dividerLineY = headingPosY + 60;
    std::cout << "OKE" << std::endl;
    
    heading.setHasHeading(true);
    heading.init("../assets/fonts/Redressed.ttf", 
                 confirmMessage, 
                 headingPosY, 
                 fontSize, 
                 {(GraphicsComponentManager::NATIVE_WIDTH - dividerLineLength) / 2, 
                  dividerLineY, 
                  0, 
                  0},
                 StateHeading::Alignment::RIGHT,
                 300);
    heading.setLayer(200);
    setupButtons();
}

void ConfirmState::setupButtons() {
    int buttonWidth = GraphicsComponentManager::NATIVE_WIDTH;
    int buttonHeight = 80;
    int coordYFirstButton = 320;
    int buttonSpacing = 20;
    int offset = 100;
    int deltaOffset = -50;
    int fontSize = 75;
    
    // Yes button (left of center)
    std::unique_ptr<Button> yesButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        yesButtonText, 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );

    yesButton->setLayer(200);
    yesButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        // Set the result to true (YES)
        result = true;
        
        // Call the callback if set
        if (onConfirmCallback) {
            onConfirmCallback(true);
        }
        
        // Return to previous state
        gameStateManager.popState();
    });
    yesButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(yesButton));

    // No button (right of center)
    std::unique_ptr<Button> noButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        noButtonText, 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    noButton->setLayer(200);
    noButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        // Set the result to false (NO)
        result = false;
        
        // Call the callback if set
        if (onConfirmCallback) {
            onConfirmCallback(false);
        }
        
        // Return to previous state
        gameStateManager.popState();
    });
    noButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(noButton));
}

void ConfirmState::update(float dt) {
    if (!visible) {
        setVisible(true);
    }
    buttonManager.update(dt);
}

void ConfirmState::exit() {
    buttonManager.reset();
}

void ConfirmState::setVisible(bool visible) {
    this->visible = visible;
    buttonManager.setVisible(visible);
    heading.setVisible(visible);
}

void ConfirmState::setOnConfirmCallback(std::function<void(bool)> callback) {
    onConfirmCallback = callback;
}