#include "GameplayPauseState.hpp"
#include "../GameStateManager.hpp"
#include "../main_menu_state/MainMenuState.hpp"
#include "../char_select_state/CharSelectState.hpp"
#include "../../../audio/AudioManager.hpp"

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
    int coordYFirstButton = 140;
    int buttonSpacing = 20;
    int offset = 0;
    int deltaOffset = 0;
    int fontSize = 50;
    
    // Setup heading
    heading.setHasHeading(true);
    int dividerLineHeight = 2;
    int dividerLineLength = 600;
    int dividerLineThickness = 5;
    int headingPosY = 130;
    int dividerLineY = headingPosY + 60;
    heading.init("../assets/fonts/18thCentury.ttf", "PAUSED", headingPosY, fontSize, 
                {(GetScreenWidth() - dividerLineLength) / 2, dividerLineY, dividerLineLength, dividerLineThickness});
    
    // Resume button
    std::unique_ptr<Button> resumeButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "RESUME", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
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
        "CHARACTER SELECT", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    charSelectButton->setLayer(100);
    charSelectButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        selectedOption = PauseMenuOption::CHARACTER_SELECT;
        gameStateManager.popState();
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
        "MAIN MENU", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    mainMenuButton->setLayer(100);
    mainMenuButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        selectedOption = PauseMenuOption::MAIN_MENU;
        gameStateManager.popState();
    });
    mainMenuButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(mainMenuButton));
}

void GameplayPauseState::update(float dt) {
    if (!visible) {
        setVisible(true);
    }
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));
    buttonManager.update(dt);
}

void GameplayPauseState::exit() {
    buttonManager.reset();
}

void GameplayPauseState::setVisible(bool visible) {
    this->visible = visible;
    buttonManager.setVisible(visible);
    heading.setVisible(visible);
}