#include "MainMenuState.hpp"
#include "../GameStateManager.hpp"
#include "../solo_mode_state/SoloModeState.hpp"
#include "../../../audio/AudioManager.hpp"

MainMenuState::MainMenuState(GameStateManager& gsm) : gameStateManager(gsm)
{
    // , background("../assets/background/main_menu_background.png")
    background.loadTexture("../assets/background/main_menu_background_new.png");
    enter();
}

MainMenuState::~MainMenuState(){
    AudioManager::getInstance().unloadThemeMusic();
}

void MainMenuState::enter() {
    std::unique_ptr<Button> startButton = std::make_unique<Button>(0, 50, 700, 100, "Start Game");
    startButton->setOnClickListener([this]() {
        AudioManager::getInstance().play("ClickButton");
        gameStateManager.changeState(std::make_unique<SoloModeState>(gameStateManager));
    });
    startButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Start Game button!" << std::endl;
        AudioManager::getInstance().play("MenuCursor");
    });
    buttonManager.addButton(std::move(startButton));
    std::unique_ptr<Button> exitButton = std::make_unique<Button>(0, 150, 700, 100, "Exit Game");
    exitButton->setOnClickListener([this]() {
        std::cout << "Exiting game!" << std::endl;
        AudioManager::getInstance().play("ClickButton");
    });
    exitButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Exit Game button!" << std::endl;
        AudioManager::getInstance().play("MenuCursor");
    });
    buttonManager.addButton(std::move(exitButton));
    AudioManager::getInstance().loadThemeMusic("../assets/audio/music_mainthema.ogg");
}

void MainMenuState::update(float dt) {
    buttonManager.update(dt);
    AudioManager::getInstance().update(dt);
}

void MainMenuState::exit() {
}