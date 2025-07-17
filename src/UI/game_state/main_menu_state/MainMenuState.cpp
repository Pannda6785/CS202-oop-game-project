#include "MainMenuState.hpp"
#include "../GameStateManager.hpp"
#include "../solo_mode_state/SoloModeState.hpp"
#include "../../../audio/AudioManager.hpp"

MainMenuState::MainMenuState(GameStateManager& gsm) : gameStateManager(gsm)
{
    background.loadTexture("../assets/background/main_menu_background_new.png");
    // background.loadTexture("../assets/background/tile_pattern.png");
    movingTileEffect[0].loadTexture("../assets/background/tile_pattern_0.png");
    movingTileEffect[0].loadSideLines("../assets/background/side_lines.png");
    movingTileEffect[1].loadTexture("../assets/background/tile_pattern_1.png");
    // movingTileEffect.loadTexture("../assets/background/tile_pattern.png");
    // movingTileEffect.loadTexture("../assets/background/main_menu_background_new.png");
    enter();
}

MainMenuState::~MainMenuState(){
    AudioManager::getInstance().unloadThemeMusic();
}

void MainMenuState::enter() {
    int buttonWidth = 700;
    int buttonHeight = 75;
    int coordYFirstButton = 50;
    std::unique_ptr<Button> startButton = std::make_unique<Button>(0, coordYFirstButton += buttonHeight, buttonWidth, buttonHeight, "Start Game");
    startButton->setOnClickListener([this]() {
        AudioManager::getInstance().play("ClickButton");
        gameStateManager.changeState(std::make_unique<SoloModeState>(gameStateManager));
    });
    startButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Start Game button!" << std::endl;
        AudioManager::getInstance().play("MenuCursor");
    });
    buttonManager.addButton(std::move(startButton));
    std::unique_ptr<Button> exitButton = std::make_unique<Button>(0, coordYFirstButton += buttonHeight, buttonWidth, buttonHeight, "Exit Game");
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
    movingTileEffect[0].init({350, 0}, 20.0f, 100.0f, 10);
    movingTileEffect[1].init({400, 0}, 30.0f, 120.0f, 9);
}

void MainMenuState::update(float dt) {
    buttonManager.update(dt);
    for(int i = 0; i < 2; i++) movingTileEffect[i].update(dt);
    // movingTileEffect[0].update(dt);
    AudioManager::getInstance().update(dt);
}

void MainMenuState::exit() {
}