#include "KeybindingState.hpp"
#include "KeybindingConfigState.hpp"
#include "../GameStateManager.hpp"
#include "../../../audio/AudioManager.hpp"
#include <iostream>

// Forward declare the KeybindingConfigState
class KeybindingConfigState;

KeybindingState::KeybindingState(GameStateManager &gameStateManager, BehindDots &behindDots) 
: gameStateManager(gameStateManager), behindDots(behindDots) {
    enter();
}

KeybindingState::~KeybindingState() {
    exit();
}

void KeybindingState::enter() {
    // Set up the heading
    heading.setHasHeading(true);
    int fontSize = 60;
    int dividerLineLength = 600;
    int dividerLineThickness = 5;
    int headingPosY = 150;
    int dividerLineY = headingPosY + 70;
    heading.init(
        "../assets/fonts/18thCentury.ttf", 
        "INPUT OPTIONS", 
        headingPosY, 
        fontSize, 
        {(GetScreenWidth() - dividerLineLength) / 2, dividerLineY, dividerLineLength, dividerLineThickness}
    );
    
    // Player selection instruction text
    // Would be displayed between heading and buttons
    
    // Calculate positions for the player buttons
    int buttonWidth = 400;
    int buttonHeight = 100;
    int buttonSpacing = 80;
    int buttonY = GetScreenHeight() / 2 - 50; // Centered vertically
    
    // Player 1 button
    std::unique_ptr<Button> player1Button = std::make_unique<Button>(
        GetScreenWidth() / 2 - buttonWidth - buttonSpacing / 2, 
        buttonY, 
        buttonWidth, 
        buttonHeight, 
        "PLAYER 1", 
        50, 
        0, 
        0, // Center aligned
        "../assets/fonts/18thCentury.ttf",
        true // use outline
    );
    player1Button->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setVisible(false);
        // Push the KeybindingConfigState for player 1
        gameStateManager.pushState(std::make_unique<KeybindingConfigState>(gameStateManager, behindDots, 0));
        std::cout << "Configuring Player 1 Controls" << std::endl;
    });
    player1Button->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(player1Button));
    
    // Player 2 button
    std::unique_ptr<Button> player2Button = std::make_unique<Button>(
        GetScreenWidth() / 2 + buttonSpacing / 2, 
        buttonY, 
        buttonWidth, 
        buttonHeight, 
        "PLAYER 2", 
        50, 
        0, 
        0, // Center aligned
        "../assets/fonts/18thCentury.ttf",
        true // use outline
    );
    player2Button->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setVisible(false);
        // Push the KeybindingConfigState for player 2
        gameStateManager.pushState(std::make_unique<KeybindingConfigState>(gameStateManager, behindDots, 1));
        std::cout << "Configuring Player 2 Controls" << std::endl;
    });
    player2Button->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(player2Button));
    
    // Return button
    std::unique_ptr<Button> returnButton = std::make_unique<Button>(
        GetScreenWidth() / 2 - 150, 
        buttonY + buttonHeight + 80, 
        300, 
        70, 
        "RETURN", 
        40, 
        0, 
        0, // Center aligned
        "../assets/fonts/18thCentury.ttf",
        true
    );
    returnButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        gameStateManager.popState();
    });
    returnButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(returnButton));
}

void KeybindingState::update(float dt) {
    if (!visible) {
        setVisible(true);
    }
    buttonManager.update(dt);
    behindDots.update(dt);
}

void KeybindingState::exit() {
    buttonManager.reset();
}

void KeybindingState::setVisible(bool visible) {
    this->visible = visible;
    buttonManager.setVisible(visible);
    heading.setVisible(visible);
}