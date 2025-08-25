#include "VersusModeState.hpp"
#include "../GameStateManager.hpp"
#include "../../../audio/AudioManager.hpp"
#include "../../button/Button.hpp"
#include "../gameplay_pause_state/GameplayPauseState.hpp"
#include "../post_gameplay_menu_state/PostGameplayMenuState.hpp"
#include "../post_gameplay_menu_state/PostGameplayMenuStateBuilder.hpp"
#include "../char_select_state/CharSelectState.hpp"

#include <iostream>

VersusModeState::VersusModeState(GameStateManager& gsm, std::unique_ptr<World> world, std::vector<std::shared_ptr<InputInterpreter>> interpreters)
    : gameStateManager(gsm), world(std::move(world)), interpreters(interpreters), selectedOption(PostGameOption::RESUME) {
}

void VersusModeState::enter() {
}

VersusModeState::~VersusModeState() {
}

void VersusModeState::update(float dt) {
    bool isGameEnded = world->isGameEnded();
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
    if(selectedOption != PostGameOption::RESUME) {
        if(selectedOption == PostGameOption::CHARACTER_SELECT) {
            // Handle character select
            std::cout << "HANDLE CHARACTER SELECT" << std::endl;
            gameStateManager.changeCurrentState(std::make_unique<CharSelectState>(gameStateManager, true));
        } else if(selectedOption == PostGameOption::MAIN_MENU) {
            // Handle main menu
            std::cout << "HANDLE MAIN MENU HUHUHUHUHUHUHUHUHUHUHUHUH" << std::endl;
            gameStateManager.popState();
            std::cout << "HANDLE MAIN MENU HIHIHIHIHIHIHIHIHIHIHIHIHIHIHIH" << std::endl;
        } else if(selectedOption == PostGameOption::RESTART) {
            // Handle restart
            std::cout << "HANDLE RESTART" << std::endl;
            selectedOption = PostGameOption::RESUME;
        }
    }
    if(paused){
        auto pauseStateBuilder = std::make_unique<PostGameplayMenuStateBuilder>(gameStateManager, selectedOption);
        pauseStateBuilder->setResumeButton()
                         .setRestartButton()
                         .setCharSelectButton()
                         .setMainMenuButton()
                         .setHeaderText("PAUSED");
        gameStateManager.pushState(pauseStateBuilder->build());
    }
    if(isGameEnded && selectedOption == PostGameOption::RESUME) {
        auto endGameStateBuilder = std::make_unique<PostGameplayMenuStateBuilder>(gameStateManager, selectedOption);
        endGameStateBuilder->setRestartButton()
                         .setCharSelectButton()
                         .setMainMenuButton()
                         .setHeaderText(world->getFinalResults());
        gameStateManager.pushState(endGameStateBuilder->build());
    }
}

void VersusModeState::exit() {
}