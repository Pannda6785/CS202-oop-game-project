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
    behindDots.loadDotTexture("../assets/UI_sprites/arround_dot.png");
    enter();
}

MainMenuState::~MainMenuState(){
    AudioManager::getInstance().unloadThemeMusic();
    behindDots.unloadDotTexture();
}

void MainMenuState::enter() {
    int buttonWidth = 720;
    int buttonHeight = 100;
    int coordYFirstButton = 50;
    int offset = 250;
    int deltaOffset = 15;
    int fontSize = 70;
    // Story button
    std::unique_ptr<Button> storyButton = std::make_unique<Button>(0, coordYFirstButton += buttonHeight, buttonWidth, buttonHeight, "STORY", fontSize, offset -= deltaOffset, false);
    storyButton->setOnClickListener([this]() {
        AudioManager::getInstance().play("ClickButton");
        std::cout << "Story" << std::endl;
    });
    storyButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Story button!" << std::endl;
        AudioManager::getInstance().play("MenuCursor");
    });
    buttonManager.addButton(std::move(storyButton));
    // Versus button
    std::unique_ptr<Button> versusButton = std::make_unique<Button>(0, coordYFirstButton += buttonHeight, buttonWidth, buttonHeight, "VERSUS", fontSize, offset -= deltaOffset, false);
    versusButton->setOnClickListener([this]() {
        AudioManager::getInstance().play("ClickButton");
        gameStateManager.changeState(std::make_unique<SoloModeState>(gameStateManager));
    });
    versusButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Versus button!" << std::endl;
        AudioManager::getInstance().play("MenuCursor");
    });
    buttonManager.addButton(std::move(versusButton));
    // Network button
    std::unique_ptr<Button> networkButton = std::make_unique<Button>(0, coordYFirstButton += buttonHeight, buttonWidth, buttonHeight, "NETWORK", fontSize, offset -= deltaOffset, false);
    networkButton->setOnClickListener([this]() {
        AudioManager::getInstance().play("ClickButton");
    });
    networkButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Network button!" << std::endl;
        AudioManager::getInstance().play("MenuCursor");
    });
    buttonManager.addButton(std::move(networkButton));
    // Extras button
    std::unique_ptr<Button> extrasButton = std::make_unique<Button>(0, coordYFirstButton += buttonHeight, buttonWidth, buttonHeight, "EXTRAS", fontSize, offset -= deltaOffset, false);
    extrasButton->setOnClickListener([this]() {
        AudioManager::getInstance().play("ClickButton");
    });
    extrasButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Extra button!" << std::endl;
        AudioManager::getInstance().play("MenuCursor");
    });
    buttonManager.addButton(std::move(extrasButton));
    // Options button
    std::unique_ptr<Button> optionsButton = std::make_unique<Button>(0, coordYFirstButton += buttonHeight, buttonWidth, buttonHeight, "OPTIONS", fontSize, offset -= deltaOffset, false);
    optionsButton->setOnClickListener([this]() {
        AudioManager::getInstance().play("ClickButton");
    });
    optionsButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Extra button!" << std::endl;
        AudioManager::getInstance().play("MenuCursor");
    });
    buttonManager.addButton(std::move(optionsButton));

    // Exit button
    std::unique_ptr<Button> exitButton = std::make_unique<Button>(0, coordYFirstButton += buttonHeight, buttonWidth, buttonHeight, "EXIT GAME", fontSize, offset -= deltaOffset, false);
    exitButton->setOnClickListener([this]() {
        std::cout << "Exiting game!" << std::endl;
        AudioManager::getInstance().play("ClickButton");
        gameStateManager.popState();
    });
    exitButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Exit Game button!" << std::endl;
        AudioManager::getInstance().play("MenuCursor");
    });
    buttonManager.addButton(std::move(exitButton));
    AudioManager::getInstance().loadThemeMusic("../assets/audio/music_mainthema.ogg");
    movingTileEffect[0].init({500, 0}, 10.0f, 100.0f, 10);
    movingTileEffect[1].init({550, 0}, 6.0f, 120.0f, 9);
    behindDots.init();
}

void MainMenuState::update(float dt) {
    buttonManager.update(dt);
    for(int i = 0; i < 2; i++) movingTileEffect[i].update(dt);
    AudioManager::getInstance().update(dt);
    behindDots.update(dt);
}

void MainMenuState::exit() {
}