#include "MainMenuState.hpp"
#include "../GameStateManager.hpp"
#include "../solo_mode_state/SoloModeState.hpp"
#include "../versus_mode_state/versus_player_state/VersusPlayerState.hpp"
#include "../char_select_state/CharSelectState.hpp"
#include "../options_state/OptionsState.hpp"
#include "../../../audio/AudioManager.hpp"

MainMenuState::MainMenuState(GameStateManager& gsm) : gameStateManager(gsm)
{
    enter();
}

MainMenuState::~MainMenuState(){
    exit();
}

void MainMenuState::enter() {
    setVisible(true);
    heading.setHasHeading(false);
    artworkTitle.loadCharTexture("../assets/background/main_menu_char.png");
    artworkTitle.loadTitleTexture("../assets/background/main_menu_title.png");
    artworkTitle.loadDecorationTexture("../assets/background/main_menu_decoration.png");
    movingTileEffect[0].addTexture("../assets/background/tile_pattern_0.png");
    movingTileEffect[0].addTexture("../assets/background/side_lines.png");
    movingTileEffect[1].addTexture("../assets/background/tile_pattern_1.png");
    for(int i = 0; i < 2; i++){
        movingTileEffect[i].setRestrictArea({0.0f, -100.0f, (float)GetScreenWidth(), (float)GetScreenHeight() + 100.0f});
    }
    behindDots.loadDotTexture("../assets/UI_sprites/arround_dot.png");
    int buttonWidth = 720;
    int buttonHeight = 100;
    int coordYFirstButton = 50;
    int offset = 250;
    int deltaOffset = 15;
    int fontSize = 70;
    // Story button
    std::unique_ptr<Button> storyButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight, 
        buttonWidth, 
        buttonHeight, 
        "STORY", 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    storyButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        std::cout << "Story" << std::endl;
    });
    storyButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Story button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(storyButton));
    // Versus button
    std::unique_ptr<Button> versusButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight, 
        buttonWidth, buttonHeight, 
        "VERSUS", 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    versusButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        // gameStateManager.changeState(std::make_unique<SoloModeState>(gameStateManager));
        setVisible(false);
        gameStateManager.pushState(std::make_unique<CharSelectState>(gameStateManager));
        // gameStateManager.pushState(std::make_unique<VersusPlayerState>(gameStateManager, "Sun Priestess", "Hero of Frost"));
    });
    versusButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Versus button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(versusButton));
    // Network button
    std::unique_ptr<Button> networkButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight, 
        buttonWidth, 
        buttonHeight, 
        "NETWORK", 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    networkButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
    });
    networkButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Network button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(networkButton));
    // Extras button
    std::unique_ptr<Button> extrasButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight, 
        buttonWidth, 
        buttonHeight, 
        "EXTRAS", 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    extrasButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
    });
    extrasButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Extra button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(extrasButton));

    // Options button
    std::unique_ptr<Button> optionsButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight, 
        buttonWidth, 
        buttonHeight, 
        "OPTIONS", 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    optionsButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setVisible(false);
        gameStateManager.pushState(std::make_unique<OptionsState>(gameStateManager, behindDots));
    });
    optionsButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Extra button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(optionsButton));

    // Exit button
    std::unique_ptr<Button> exitButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight, 
        buttonWidth, 
        buttonHeight, 
        "EXIT", 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    exitButton->setOnClickListener([this]() {
        std::cout << "Exiting game!" << std::endl;
        AudioManager::getInstance().playSound("ClickButton");
        gameStateManager.popState();
    });
    exitButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Exit Game button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(exitButton));
    movingTileEffect[0].setStartPosition({500.0f, 0.0f});
    movingTileEffect[0].setAngle(10.0f);
    movingTileEffect[0].setSpeed(100.0f);
    movingTileEffect[0].setLayer(10);
    movingTileEffect[0].init();
    movingTileEffect[1].setStartPosition({550.0f, 0.0f});
    movingTileEffect[1].setAngle(6.0f);
    movingTileEffect[1].setSpeed(120.0f);
    movingTileEffect[1].setLayer(9);
    movingTileEffect[1].init();
    behindDots.init();
}

void MainMenuState::update(float dt) {
    if(!isVisible){
        setVisible(true);
    }
    buttonManager.update(dt);
    for(int i = 0; i < 2; i++) movingTileEffect[i].update(dt);
    behindDots.update(dt);
}

void MainMenuState::exit() {
    // AudioManager::getInstance().unloadThemeMusic();
    behindDots.unloadTexture();
    for(int i = 0; i < 2; i++) {
        movingTileEffect[i].unloadTextures();
    }
    artworkTitle.unloadTextures();
    buttonManager.reset();
}

void MainMenuState::setVisible(bool visible){
    isVisible = visible;
    buttonManager.setVisible(visible);
    artworkTitle.setVisible(visible);
    for(int i = 0; i < 2; i++) movingTileEffect[i].setVisible(visible);
    behindDots.setVisible(visible);
}