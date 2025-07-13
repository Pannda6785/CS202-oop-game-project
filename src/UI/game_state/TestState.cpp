#include "TestState.hpp"
#include "GameStateManager.hpp"
#include "MainMenuState.hpp"
#include <iostream>

TestState::TestState(GameStateManager& gsm)
    : gameStateManager(gsm)
{
    enter();
}

TestState::~TestState() = default;

void TestState::enter() {
    std::unique_ptr<Button> backButton = std::make_unique<Button>(
        50, 100, 200, 50, "Back to Main Menu", Unit::GameEvent{"back to main menu"}
    );
    backButton->setOnClickListener([&gsm = gameStateManager]() {
        std::cout << "Returning to Main Menu..." << std::endl;
        gsm.changeState(std::make_unique<MainMenuState>(gsm));
    });
    backButton->setOnHoverEnterListener([]() {
        std::cout << "Hovered over Back button!" << std::endl;
    });
    buttonManager.addButton(std::move(backButton));
}

void TestState::update(float dt) {
    buttonManager.update(dt);
}

void TestState::exit() {}