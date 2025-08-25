#include "SettingOptionsState.hpp"
#include "../../GameStateManager.hpp"
#include "../../../../audio/AudioManager.hpp"
#include "../../../../game/WorldBuilder.hpp"
#include <iostream>

SettingOptionsState::SettingOptionsState(GameStateManager& gsm, WorldBuilder& worldBuilder)
    : gameStateManager(gsm), worldBuilder(worldBuilder) {
    // Get available challenges if worldBuilder is provided
    availableChallenges = worldBuilder.getAvailableChallenges();
    enter();
    updateButtonLabels();
}

SettingOptionsState::~SettingOptionsState() {
    exit();
}

void SettingOptionsState::enter() {
    background.setBackgroundColor({0, 0, 0, 200}); // Semi-transparent black
    background.setBackgroundRect({0, 0, GraphicsComponentManager::NATIVE_WIDTH, GraphicsComponentManager::NATIVE_HEIGHT});
    background.setLayer(200);
    // Layout parameters
    int buttonWidth = GraphicsComponentManager::NATIVE_WIDTH;
    int buttonHeight = 80;
    int coordYFirstButton = 140;
    int buttonSpacing = 15;
    int offset = 0;
    int deltaOffset = 0;
    int fontSize = 50;

    for(int i = 0; i < availableChallenges.size(); i++){
        std::unique_ptr<Button> challengeButton = std::make_unique<Button>(
            0, 
            coordYFirstButton, 
            buttonWidth, 
            buttonHeight, 
            "CHALLENGE: " + availableChallenges[i], 
            fontSize, 
            offset -= deltaOffset, 
            0, 
            "../assets/fonts/18thCentury.ttf",
            false
        );
        coordYFirstButton += buttonHeight + buttonSpacing;
        challengeButton->setOnClickListener([this, i]() {
            AudioManager::getInstance().playSound("ClickButton");
            worldBuilder.setChallenge(availableChallenges[i]);
            // Handle challenge selection
            updateButtonLabels();
        });
        challengeButton->setOnHoverEnterListener([this]() {
            AudioManager::getInstance().playSound("MenuCursor");
        });
        challengeButton->setLayer(210);
        buttonManager.addButton(std::move(challengeButton));
    }
    
    // Return button
    std::unique_ptr<Button> returnButton = std::make_unique<Button>(
        0, 
        coordYFirstButton, 
        buttonWidth, 
        buttonHeight, 
        "RETURN", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    coordYFirstButton += buttonHeight + buttonSpacing;
    returnButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        gameStateManager.popState();
    });
    returnButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    returnButton->setLayer(210);
    buttonManager.addButton(std::move(returnButton));
}

void SettingOptionsState::update(float dt) {
    if (!visible) {
        setVisible(true);
    }
    buttonManager.update(dt);
}

void SettingOptionsState::exit() {
    buttonManager.reset();
}

void SettingOptionsState::setVisible(bool visible) {
    this->visible = visible;
    buttonManager.setVisible(visible);      
}

void SettingOptionsState::updateButtonLabels() {
    auto& buttons = buttonManager.getButtons();
    for(int i = 0; i < 6; i++){
        std::string challengeText = "CHALLENGE: " + availableChallenges[i];
        // Capitalize challengeText
        for (auto& c : challengeText) c = std::toupper(c);
        std::string text = challengeText + (worldBuilder.getChallengeFlags()[i] ? " (ON)" : " (OFF)");
        
        buttons[i]->setText(text);
    }
}