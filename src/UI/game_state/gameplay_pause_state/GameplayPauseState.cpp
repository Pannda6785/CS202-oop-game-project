#include "GameplayPauseState.hpp"
#include "../GameStateManager.hpp"
#include "../main_menu_state/MainMenuState.hpp"
#include "../char_select_state/CharSelectState.hpp"
#include "../../../audio/AudioManager.hpp"
#include "../confirm_state/ConfirmState.hpp"
#include <iostream>

GameplayPauseState::GameplayPauseState(GameStateManager &gameStateManager, PauseMenuOption &selectedOption) 
: gameStateManager(gameStateManager), selectedOption(selectedOption) {
    enter();
}

GameplayPauseState::~GameplayPauseState() {
    exit();
}

void GameplayPauseState::enter() {
    int buttonWidth = GetScreenWidth();
    int buttonHeight = 80;
    int coordYFirstButton = 320;
    int buttonSpacing = 20;
    int offset = 50;
    int deltaOffset = -50;
    int fontSize = 75;
    
    // Resume button
    std::unique_ptr<Button> resumeButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "resume", 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    resumeButton->setLayer(100);
    resumeButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        selectedOption = PauseMenuOption::RESUME;
        gameStateManager.popState();
    });
    resumeButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(resumeButton));

    // Back to Character Select button
    std::unique_ptr<Button> charSelectButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "character select", 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    charSelectButton->setLayer(100);
    charSelectButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        // selectedOption = PauseMenuOption::CHARACTER_SELECT;
        // gameStateManager.popState();
        setVisible(false);
        choosingOption = PauseMenuOption::CHARACTER_SELECT;
        gameStateManager.pushState(std::make_unique<ConfirmState>(gameStateManager, confirm, "are you sure?"));
    });
    charSelectButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(charSelectButton));

    // Back to Main Menu button
    std::unique_ptr<Button> mainMenuButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "main menu", 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    mainMenuButton->setLayer(100);
    mainMenuButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        // selectedOption = PauseMenuOption::MAIN_MENU;
        // gameStateManager.popState();
        setVisible(false);
        choosingOption = PauseMenuOption::MAIN_MENU;
        gameStateManager.pushState(std::make_unique<ConfirmState>(gameStateManager, confirm, "Are you sure?"));
    });
    mainMenuButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(mainMenuButton));
    background.setLayer(90);
    background.setBackgroundColor({0, 0, 0, 200});
    background.setBackgroundRect({0, 0, GetScreenWidth(), GetScreenHeight()});

    ribbonManager.addPause();
}

void GameplayPauseState::update(float dt) {
    if (!visible) {
        setVisible(true);
    }
    buttonManager.update(dt);
    ribbonManager.update(dt);
    if(confirm){
        switch(choosingOption){
            case PauseMenuOption::CHARACTER_SELECT:
                selectedOption = PauseMenuOption::CHARACTER_SELECT;
                gameStateManager.popState();
                break;
            case PauseMenuOption::MAIN_MENU:
                selectedOption = PauseMenuOption::MAIN_MENU;
                gameStateManager.popState();
                break;
            default:
                break;
        }
    }
}

void GameplayPauseState::exit() {
    buttonManager.reset();
    ribbonManager.clear();
}

void GameplayPauseState::setVisible(bool visible) {
    this->visible = visible;
    buttonManager.setVisible(visible);
    ribbonManager.setVisible(visible);
}