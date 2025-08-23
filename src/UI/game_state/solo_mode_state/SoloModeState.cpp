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
#include "../../../game/ai/GeneralAIInterpreter.hpp"

#include <iostream>

SoloModeState::SoloModeState(GameStateManager& gsm)
    : gameStateManager(gsm)
{
    enter();
}

SoloModeState::~SoloModeState(){
    std::cout << "SoloModeState destructor called." << std::endl;
}

void SoloModeState::enter() {
 
    world = std::make_unique<World>();

    /* Single Player */ {
        inputInterpreters = { std::make_shared<KeyboardInputInterpreter>() };

        std::unique_ptr<Player> player1 = std::make_unique<Player>(0, world.get(), world.get(), std::make_unique<Hero>(), inputInterpreters[0], 1, 5);
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
    
    std::unique_ptr<Button> backButton = std::make_unique<Button>(
        50, 
        50, 
        500, 
        75, 
        "Back to Main Menu", 
        50, 
        50, 
        0, 
        "../assets/fonts/Redressed.ttf",
        true
    );
    backButton->setOnClickListener([&gsm = gameStateManager]() {
        std::cout << "Returning to Main Menu..." << std::endl;
        gsm.changeState(std::make_unique<MainMenuState>(gsm));
        AudioManager::getInstance().playSound("tick");
    });
    backButton->setOnHoverEnterListener([]() {
        std::cout << "Hovered over Back button!" << std::endl;
        AudioManager::getInstance().playSound("tick");
    });
    // buttonManager.addButton(std::move(backButton));
}

void SoloModeState::update(float dt) {
    // Update input interpreters and world if needed
    for (size_t i = 0; i < inputInterpreters.size(); i++)
        inputInterpreters[i]->update(dt);
    world->update(dt);

    buttonManager.update(dt);
}

void SoloModeState::exit() {
}