#include "PostGameplayMenuState.hpp"
#include "../GameStateManager.hpp"
#include "../../../audio/AudioManager.hpp"
#include "../confirm_state/ConfirmState.hpp"
#include <iostream>

PostGameplayMenuState::PostGameplayMenuState(GameStateManager &gameStateManager, PostGameOption &selectedOption) 
    : gameStateManager(gameStateManager), selectedOption(selectedOption) {
}

PostGameplayMenuState::~PostGameplayMenuState() {
    exit();
}

void PostGameplayMenuState::enter() {
    // Initialize layout variables
    int coordY = coordYFirstButton;
    int currentOffset = offset;
    
    // Add buttons based on configuration
    if (hasResumeButton) {
        addResumeButton(coordY, currentOffset);
    }
    
    if (hasRestartButton) {
        addRestartButton(coordY, currentOffset);
    }
    
    if (hasCharSelectButton) {
        addCharSelectButton(coordY, currentOffset);
    }
    
    if (hasMainMenuButton) {
        addMainMenuButton(coordY, currentOffset);
    }
    
    // Set up background
    background.setLayer(90);
    background.setBackgroundColor({0, 0, 0, 200});
    background.setBackgroundRect({0, 0, GraphicsComponentManager::NATIVE_WIDTH, GraphicsComponentManager::NATIVE_HEIGHT});

    // Add header ribbon
    ribbonManager.addAnnouncement(headerText);
}

void PostGameplayMenuState::update(float dt) {
    if (!visible) {
        setVisible(true);
    }
    buttonManager.update(dt);
    ribbonManager.update(dt);
    
    if(confirm){
        switch(choosingOption){
            case PostGameOption::CHARACTER_SELECT:
                selectedOption = PostGameOption::CHARACTER_SELECT;
                gameStateManager.popState();
                break;
            case PostGameOption::MAIN_MENU:
                selectedOption = PostGameOption::MAIN_MENU;
                gameStateManager.popState();
                break;
            case PostGameOption::RESTART:
                selectedOption = PostGameOption::RESTART;
                gameStateManager.popState();
                break;
            default:
                break;
        }
        // gameStateManager.popState();
    }
}

void PostGameplayMenuState::exit() {
    buttonManager.reset();
    ribbonManager.clear();
}

void PostGameplayMenuState::setVisible(bool visible) {
    this->visible = visible;
    buttonManager.setVisible(visible);
    ribbonManager.setVisible(visible);
}

PostGameOption PostGameplayMenuState::getSelectedOption() const {
    return selectedOption;
}

void PostGameplayMenuState::addResumeButton(int& coordY, int& offsetX) {
    std::unique_ptr<Button> resumeButton = std::make_unique<Button>(
        0, 
        coordY += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "resume", 
        fontSize, 
        offsetX -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    resumeButton->setLayer(100);
    resumeButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        selectedOption = PostGameOption::RESUME;
        gameStateManager.popState();
    });
    resumeButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(resumeButton));
}

void PostGameplayMenuState::addRestartButton(int& coordY, int& offsetX) {
    std::unique_ptr<Button> restartButton = std::make_unique<Button>(
        0, 
        coordY += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "restart", 
        fontSize, 
        offsetX -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    restartButton->setLayer(100);
    restartButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setVisible(false);
        choosingOption = PostGameOption::RESTART;
        gameStateManager.pushState(std::make_unique<ConfirmState>(gameStateManager, confirm));
    });
    restartButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(restartButton));
}

void PostGameplayMenuState::addCharSelectButton(int& coordY, int& offsetX) {
    std::unique_ptr<Button> charSelectButton = std::make_unique<Button>(
        0, 
        coordY += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "character select", 
        fontSize, 
        offsetX -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    charSelectButton->setLayer(100);
    charSelectButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setVisible(false);
        choosingOption = PostGameOption::CHARACTER_SELECT;
        gameStateManager.pushState(std::make_unique<ConfirmState>(gameStateManager, confirm));
    });
    charSelectButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(charSelectButton));
}

void PostGameplayMenuState::addMainMenuButton(int& coordY, int& offsetX) {
    std::unique_ptr<Button> mainMenuButton = std::make_unique<Button>(
        0, 
        coordY += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "main menu", 
        fontSize, 
        offsetX -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    mainMenuButton->setLayer(100);
    mainMenuButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setVisible(false);
        choosingOption = PostGameOption::MAIN_MENU;
        gameStateManager.pushState(std::make_unique<ConfirmState>(gameStateManager, confirm));
    });
    mainMenuButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(mainMenuButton));
}