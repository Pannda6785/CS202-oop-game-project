#include "VersusModeState.hpp"
#include "../GameStateManager.hpp"
#include "../../../audio/AudioManager.hpp"
#include "../../button/Button.hpp"
#include "../gameplay_pause_state/GameplayPauseState.hpp"
#include "../char_select_state/CharSelectState.hpp"

#include <iostream>

VersusModeState::VersusModeState(GameStateManager& gsm, std::unique_ptr<World> world, std::vector<std::shared_ptr<InputInterpreter>> interpreters)
    : gameStateManager(gsm), world(std::move(world)), interpreters(interpreters), selectedOption(PauseMenuOption::RESUME) {
}

void VersusModeState::enter() {
}

VersusModeState::~VersusModeState() {
}

void VersusModeState::update(float dt) {
    if (world) {
        world->update(dt);
    }
    for(auto &interpreter : interpreters) {
        interpreter->update(dt);
    }
    bool paused = false;
    for(const auto& interpreter : interpreters) {
        if (interpreter->isInputDown(Unit::Input::Pause)) {
            paused = true;
            break;
        }
    }
    if(paused){
        gameStateManager.pushState(std::make_unique<GameplayPauseState>(gameStateManager, selectedOption));
    }
    if(selectedOption != PauseMenuOption::RESUME) {
        if(selectedOption == PauseMenuOption::CHARACTER_SELECT) {
            // Handle character select
            gameStateManager.changeCurrentState(std::make_unique<CharSelectState>(gameStateManager, true));
        } else if(selectedOption == PauseMenuOption::MAIN_MENU) {
            // Handle main menu
            gameStateManager.popState();
        }
    }
}

void VersusModeState::exit() {
}