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
    int buttonWidth = GetScreenWidth();
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
        {(GetScreenWidth() - dividerLineLength) / 2, dividerLineY, dividerLineLength, dividerLineThickness}
    );

    // Native resolution button (1440x900)
    std::unique_ptr<Button> nativeResButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "NATIVE RESOLUTION (1440x900)", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    nativeResButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setResolution(1440, 900);
        updateButtonStates();
    });
    nativeResButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    resolutionNativeButtonIndex = cntButton++;
    buttonManager.addButton(std::move(nativeResButton));

    // 1080p resolution button (1920x1080)
    std::unique_ptr<Button> res1080pButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "HD RESOLUTION (1920x1080)", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    res1080pButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setResolution(1920, 1080);
        updateButtonStates();
    });
    res1080pButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    resolution1080pButtonIndex = cntButton++;
    buttonManager.addButton(std::move(res1080pButton));

    // Fullscreen button
    std::unique_ptr<Button> fullscreenButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "FULLSCREEN: OFF", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    fullscreenButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        // Toggle fullscreen
        setFullscreen(!GraphicsComponentManager::instance().isToggleFullScreen());
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
    
    // Native resolution button
    if (resolutionNativeButtonIndex >= 0 && resolutionNativeButtonIndex < buttons.size()) {
        if (currentWidth == 1440 && currentHeight == 900 && !isFullscreen) {
            buttons[resolutionNativeButtonIndex]->setText("NATIVE RESOLUTION (1440x900) : ON");
        } else {
            buttons[resolutionNativeButtonIndex]->setText("NATIVE RESOLUTION (1440x900) : OFF");
        }
    }
    
    // 1080p resolution button
    if (resolution1080pButtonIndex >= 0 && resolution1080pButtonIndex < buttons.size()) {
        if (currentWidth == 1920 && currentHeight == 1080 && !isFullscreen) {
            buttons[resolution1080pButtonIndex]->setText("HD RESOLUTION (1920x1080) : ON");
        } else {
            buttons[resolution1080pButtonIndex]->setText("HD RESOLUTION (1920x1080) : OFF");
        }
    }
    
    // Fullscreen button
    if (fullscreenButtonIndex >= 0 && fullscreenButtonIndex < buttons.size()) {
        if (isFullscreen) {
            buttons[fullscreenButtonIndex]->setText("FULLSCREEN: ON");
        } else {
            buttons[fullscreenButtonIndex]->setText("FULLSCREEN: OFF");
        }
    }
}

void GraphicOptions::setResolution(int width, int height) {
    auto& gcm = GraphicsComponentManager::instance();
    
    // First ensure we're not in fullscreen
    if (gcm.isToggleFullScreen()) {
        gcm.toggleFullscreen();
    }
    
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