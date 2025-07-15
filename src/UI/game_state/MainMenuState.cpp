#include "MainMenuState.hpp"
#include "GameStateManager.hpp"
#include "SoloModeState.hpp"
#include "TestState.hpp"

MainMenuState::MainMenuState(GameStateManager& gsm)
    : gameStateManager(gsm)
{
    enter();
}

MainMenuState::~MainMenuState(){
    UnloadSound(buttonHoverSound);
}
void MainMenuState::enter() {
    buttonHoverSound = LoadSound("./assets/raw_sounds/sound_tick.wav");
    std::unique_ptr<Button> startButton = std::make_unique<Button>(50, 50, 200, 50, "Start Game");
    startButton->setOnClickListener([this]() {
        PlaySound(buttonHoverSound);
        gameStateManager.changeState(std::make_unique<SoloModeState>(gameStateManager));
    });
    startButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Start Game button!" << std::endl;
        PlaySound(buttonHoverSound);
    });
    buttonManager.addButton(std::move(startButton));
    std::unique_ptr<Button> exitButton = std::make_unique<Button>(50, 150, 200, 50, "Exit Game");
    exitButton->setOnClickListener([this]() {
        std::cout << "Exiting game!" << std::endl;
        PlaySound(buttonHoverSound);
    });
    exitButton->setOnHoverEnterListener([this]() {
        std::cout << "Hovered over Exit Game button!" << std::endl;
        PlaySound(buttonHoverSound);
    });
    buttonManager.addButton(std::move(exitButton));
}

void MainMenuState::update(float dt) {
    buttonManager.update(dt);
}

void MainMenuState::exit() {
}