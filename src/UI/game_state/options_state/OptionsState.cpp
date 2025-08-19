#include "OptionsState.hpp"
#include "../GameStateManager.hpp"
#include "./sound_options/SoundOptions.hpp"
#include "../../../audio/AudioManager.hpp"
#include "../keybinding_state/KeybindingState.hpp"

OptionsState::OptionsState(GameStateManager &gameStateManager, BehindDots &behindDots) 
: gameStateManager(gameStateManager), behindDots(behindDots){
    enter();
}

OptionsState::~OptionsState(){
    exit();
}

void OptionsState::enter(){
    int buttonWidth = GetScreenWidth();
    int buttonHeight = 80;
    int coordYFirstButton = 140;
    int buttonSpacing = 15;
    int offset = 0;
    int deltaOffset = 0;
    int fontSize = 50;
    heading.setHasHeading(true);
    int dividerLineHeight = 2;
    int dividerLineLength = 600;
    int dividerLineThickness = 5;
    int headingPosY = 130;
    int dividerLineY = headingPosY + 60;
    heading.init("../assets/fonts/18thCentury.ttf", "OPTIONS", headingPosY, fontSize, {(GetScreenWidth() - dividerLineLength) / 2, dividerLineY, dividerLineLength, dividerLineThickness});
    // Graphics options button
    std::unique_ptr<Button> graphicsButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "GRAPHICS OPTIONS", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    graphicsButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        std::cout << "Graphics Options" << std::endl;
    });
    graphicsButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Graphics Options button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(graphicsButton));

    // Sound options button
    std::unique_ptr<Button> soundButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "SOUND OPTIONS", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    soundButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setVisible(false);
        gameStateManager.pushState(std::make_unique<SoundOptions>(gameStateManager, behindDots));
        std::cout << "Sound Options" << std::endl;
    });
    soundButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Sound Options button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(soundButton));

    // Battle options button
    std::unique_ptr<Button> battleButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "BATTLE OPTIONS", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    battleButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        std::cout << "Battle Options" << std::endl;
    });
    battleButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Battle Options button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(battleButton));

    // Language options button
    std::unique_ptr<Button> languageButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "LANGUAGE OPTIONS", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    languageButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        std::cout << "Language Options" << std::endl;
    });
    languageButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Language Options button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(languageButton));

    // Input options button
    std::unique_ptr<Button> inputButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight + buttonSpacing, 
        buttonWidth, 
        buttonHeight, 
        "INPUT OPTIONS", 
        fontSize, 
        offset -= deltaOffset, 
        0, 
        "../assets/fonts/18thCentury.ttf",
        false
    );
    inputButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        // std::cout << "Input Options" << std::endl;
        setVisible(false);
        gameStateManager.pushState(std::make_unique<KeybindingState>(gameStateManager, behindDots));
    });
    inputButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Input Options button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(inputButton));

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
        std::cout << "Return" << std::endl;
    });
    returnButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Return button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(returnButton));
}

void OptionsState::update(float dt){
    if(!visible){
        setVisible(true);
    }
    buttonManager.update(dt);
    behindDots.update(dt);
}

void OptionsState::exit(){
    buttonManager.reset();
}

void OptionsState::setVisible(bool visible) {
    this->visible = visible;
    buttonManager.setVisible(visible);
    heading.setVisible(visible);
}