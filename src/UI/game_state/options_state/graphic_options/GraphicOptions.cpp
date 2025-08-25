#include "GraphicOptions.hpp"
#include "../../GameStateManager.hpp"
#include "../../../../audio/AudioManager.hpp"
#include "../../../../graphics/GraphicsComponentManager.hpp"
#include <iostream>

GraphicOptions::GraphicOptions(GameStateManager &gameStateManager, BehindDots &behindDots) 
    : gameStateManager(gameStateManager), behindDots(behindDots) {
    enter();
}

GraphicOptions::~GraphicOptions() {
    exit();
}

void GraphicOptions::enter() {
    // Layout parameters
    int buttonWidth = GraphicsComponentManager::NATIVE_WIDTH;
    int buttonHeight = 80;
    int coordYFirstButton = 140;
    int buttonSpacing = 15;
    int offset = 0;
    int deltaOffset = 0;
    int fontSize = 50;
    int cntButton = 0;
    
    // Set up heading
    heading.setHasHeading(true);
    int dividerLineHeight = 2;
    int dividerLineLength = 600;
    int dividerLineThickness = 5;
    int headingPosY = 130;
    int dividerLineY = headingPosY + 60;
    heading.init(
        "../assets/fonts/18thCentury.ttf", 
        "GRAPHICS OPTIONS", 
        headingPosY, 
        fontSize, 
        {(GraphicsComponentManager::NATIVE_WIDTH - dividerLineLength) / 2, dividerLineY, dividerLineLength, dividerLineThickness}
    );

    // Windowed mode button (1440x900)
    std::unique_ptr<Button> windowedButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "WINDOWED", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    windowedButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setResolution(1440, 900);
        setFullscreen(false);
        updateButtonStates();
    });
    windowedButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    windowedButtonIndex = cntButton++;
    buttonManager.addButton(std::move(windowedButton));

    // Fullscreen button
    std::unique_ptr<Button> fullscreenButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "FULLSCREEN", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    fullscreenButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setFullscreen(true);
        updateButtonStates();
    });
    fullscreenButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    fullscreenButtonIndex = cntButton++;
    buttonManager.addButton(std::move(fullscreenButton));

    // Return button
    std::unique_ptr<Button> returnButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "RETURN", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    returnButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        gameStateManager.popState();
    });
    returnButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(returnButton));
    
    // Update button states to reflect current settings
    updateButtonStates();
}

void GraphicOptions::update(float dt) {
    if (!visible) {
        setVisible(true);
    }
    buttonManager.update(dt);
    behindDots.update(dt);
}

void GraphicOptions::exit() {
    buttonManager.reset();
}

void GraphicOptions::setVisible(bool visible) {
    this->visible = visible;
    buttonManager.setVisible(visible);
    heading.setVisible(visible);
}

void GraphicOptions::updateButtonStates() {
    auto& gcm = GraphicsComponentManager::instance();
    
    // Get current state
    bool isFullscreen = gcm.isToggleFullScreen();
    int currentWidth = gcm.getWindowWidth();
    int currentHeight = gcm.getWindowHeight();
    
    // Update button labels
    auto& buttons = buttonManager.getButtons();
    
    // Windowed button
    if (windowedButtonIndex >= 0 && windowedButtonIndex < buttons.size()) {
        if (currentWidth == 1440 && currentHeight == 900 && !isFullscreen) {
            buttons[windowedButtonIndex]->setText("WINDOWED : ACTIVE");
        } else {
            buttons[windowedButtonIndex]->setText("WINDOWED");
        }
    }
    
    // Fullscreen button
    if (fullscreenButtonIndex >= 0 && fullscreenButtonIndex < buttons.size()) {
        if (isFullscreen) {
            buttons[fullscreenButtonIndex]->setText("FULLSCREEN : ACTIVE");
        } else {
            buttons[fullscreenButtonIndex]->setText("FULLSCREEN");
        }
    }
}

void GraphicOptions::setResolution(int width, int height) {
    auto& gcm = GraphicsComponentManager::instance();
    
    // Set the new resolution
    gcm.setResolution(width, height);
}

void GraphicOptions::setFullscreen(bool enable) {
    auto& gcm = GraphicsComponentManager::instance();
    
    // Toggle fullscreen only if the current state doesn't match what we want
    if (gcm.isToggleFullScreen() != enable) {
        gcm.toggleFullscreen();
    }
}