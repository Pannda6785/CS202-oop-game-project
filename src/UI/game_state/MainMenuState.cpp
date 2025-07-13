#include "MainMenuState.hpp"
#include "GameStateManager.hpp"
#include "SoloModeState.hpp"
#include "TestState.hpp"

MainMenuState::MainMenuState(GameStateManager& gsm)
    : gameStateManager(gsm)
{
    enter();
}

MainMenuState::~MainMenuState() = default;

void MainMenuState::enter() {
    std::unique_ptr<Button> startButton = std::make_unique<Button>(50, 50, 200, 50, "Start Game", Unit::GameEvent{"enter gameplay"});
    // startButton->setOnClickListener([btn = startButton.get()]() {
    //     EventManager::getInstance().publish(btn->getEventToPublish());
    // });
    startButton->setOnClickListener([&gsm = gameStateManager]() {
        gsm.changeState(std::make_unique<TestState>(gsm));
    });
    startButton->setOnHoverEnterListener([]() {
        std::cout << "Hovered over Start Game button!" << std::endl;
    });
    buttonManager.addButton(std::move(startButton));
    std::unique_ptr<Button> exitButton = std::make_unique<Button>(50, 150, 200, 50, "Exit Game", Unit::GameEvent{"exit game"});
    exitButton->setOnClickListener([]() {
        std::cout << "Exiting game!" << std::endl;
    });
    exitButton->setOnHoverEnterListener([]() {
        std::cout << "Hovered over Exit Game button!" << std::endl;
    });
    buttonManager.addButton(std::move(exitButton));
}

void MainMenuState::update(float dt) {
    buttonManager.update(dt);
}

void MainMenuState::exit() {
}