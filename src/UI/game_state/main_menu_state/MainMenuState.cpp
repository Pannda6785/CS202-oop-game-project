#include "MainMenuState.hpp"
#include "../GameStateManager.hpp"
#include "../solo_mode_state/SoloModeState.hpp"
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
    // Versus player button
    std::unique_ptr<Button> versusPlayerButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight, 
        buttonWidth, buttonHeight, 
        "VS PLAYER", 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    versusPlayerButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setVisible(false);
        gameStateManager.pushState(std::make_unique<CharSelectState>(gameStateManager, true));
    });
    versusPlayerButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Versus Player button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(versusPlayerButton));
    // Versus Com button
    std::unique_ptr<Button> versusComButton = std::make_unique<Button>(
        0,
        coordYFirstButton += buttonHeight,
        buttonWidth,
        buttonHeight,
        "VS COM",
        fontSize,
        offset -= deltaOffset,
        1,
        "../assets/fonts/Redressed.ttf",
        true
    );
    versusComButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setVisible(false);
        gameStateManager.pushState(std::make_unique<CharSelectState>(gameStateManager, false));
    });
    versusComButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Versus Com button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(versusComButton));
    // Single player button
    std::unique_ptr<Button> singleButton = std::make_unique<Button>(
        0, 
        coordYFirstButton += buttonHeight, 
        buttonWidth, 
        buttonHeight, 
        "SINGLE", 
        fontSize, 
        offset -= deltaOffset, 
        1, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    singleButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        setVisible(false);
        gameStateManager.pushState(std::make_unique<SoloModeState>(gameStateManager));
    });
    singleButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Single button!" << std::endl;
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(singleButton));
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