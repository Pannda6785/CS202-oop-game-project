#include "SoloModeState.hpp"
#include "../GameStateManager.hpp"
#include "../main_menu_state/MainMenuState.hpp"
#include "../../../audio/AudioManager.hpp"
#include "../../../game/player/Player.hpp"

#include "../../../game/character/priestess/Priestess.hpp"
#include "../../../game/character/redhood/Redhood.hpp"
#include "../../../game/character/arcanist/Arcanist.hpp"
#include "../../../game/character/hero/Hero.hpp"
#include "../../../game/character/wyrm/Wyrm.hpp"
#include "../../../game/character/lich/Lich.hpp"
#include "../../../game/character/depth/Depth.hpp"
#include "../../../game/character/stormbeast/Stormbeast.hpp"

#include "../../../game/pattern/DemoPattern.hpp"
#include "../../../game/pattern/OrichalcumMail.hpp"
#include "../../../game/pattern/CeresCurrent.hpp"
#include "../../../game/pattern/HeartPulsation.hpp"
#include "../../../game/pattern/StaticGreen.hpp"

#include "../../../input/KeyboardInputInterpreter.hpp"
#include "../../../input/InputInterpreterManager.hpp"
#include "../../../game/ai/GeneralAIInterpreter.hpp"

#include "../post_gameplay_menu_state/PostGameplayMenuState.hpp"
#include "../post_gameplay_menu_state/PostGameplayMenuStateBuilder.hpp"
#include "../gameplay_pause_state/GameplayPauseState.hpp"

#include <iostream>

SoloModeState::SoloModeState(GameStateManager& gsm)
    : gameStateManager(gsm), selectedOption(PostGameOption::RESUME)
{
    enter();
}

SoloModeState::~SoloModeState(){
    std::cout << "SoloModeState destructor called." << std::endl;
}

void SoloModeState::enter() {
 
    world = std::make_unique<World>();

    /* Single Player */ {

        std::unique_ptr<Player> player1 = std::make_unique<Player>(0, world.get(), world.get(), std::make_unique<Hero>(), InputInterpreterManager::getInstance().getInterpreter(0), 1, 5);
        
        player1->applyLock(Unit::Lock::BasicLock, 1e9, true);
        player1->applyLock(Unit::Lock::WideLock, 1e9, true);

        world->addPlayer(std::move(player1));

        world->addPattern(std::make_unique<OrichalcumMail>(world.get()), 0);
        world->addPattern(std::make_unique<CeresCurrent>(world.get()), 35);
        for (int i = 0; i < 8; i++) {
            world->addPattern(std::make_unique<HeartPulsation>(world.get()), 65 + i * (6.0f / 8.0f));
        }
        for (int i = 0; i < 2; i++) {
            world->addPattern(std::make_unique<StaticGreen>(world.get(), world.get()), 65 + i * 5);
        }
    }

   world->init();
}

void SoloModeState::update(float dt) {
    world->update(dt);

    bool paused = false;
    auto interpreter = InputInterpreterManager::getInstance().getInterpreter(0);
    if (interpreter->isInputDown(Unit::Input::Pause)) {
        paused = true;
    }

    if(selectedOption != PostGameOption::RESUME) {
        if(selectedOption == PostGameOption::MAIN_MENU) {
            // Handle main menu
            std::cout << "HANDLE MAIN MENU" << std::endl;
            gameStateManager.popState();
        }
    }

    if (paused) {
        auto pauseStateBuilder = std::make_unique<PostGameplayMenuStateBuilder>(gameStateManager, selectedOption);
        pauseStateBuilder->setResumeButton()
                         .setMainMenuButton()
                         .setHeaderText("PAUSED");
        gameStateManager.pushState(pauseStateBuilder->build());
    }
}

void SoloModeState::exit() {
}