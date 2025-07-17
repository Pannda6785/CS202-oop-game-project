#include "MainMenuState.hpp"
#include "../GameStateManager.hpp"
#include "../solo_mode_state/SoloModeState.hpp"
#include "../../../audio/AudioManager.hpp"

MainMenuState::MainMenuState(GameStateManager& gsm) : gameStateManager(gsm)
{
    background.loadCharTexture("../assets/background/main_menu_char.png");
    background.loadTitleTexture("../assets/background/main_menu_title.png");
    background.loadDecorationTexture("../assets/background/main_menu_decoration.png");
    movingTileEffect[0].loadTexture("../assets/background/tile_pattern_0.png");
    movingTileEffect[0].loadSideLines("../assets/background/side_lines.png");
    movingTileEffect[1].loadTexture("../assets/background/tile_pattern_1.png");
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
    movingTileEffect[0].init({500, 0}, 10.0f, 100.0f, 10);
    movingTileEffect[1].init({550, 0}, 6.0f, 120.0f, 9);
}

void MainMenuState::update(float dt) {
    buttonManager.update(dt);
    for(int i = 0; i < 2; i++) movingTileEffect[i].update(dt);
    AudioManager::getInstance().update(dt);
}

void MainMenuState::exit() {
}