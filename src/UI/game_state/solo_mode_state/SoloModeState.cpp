#include "SoloModeState.hpp"
#include "../GameStateManager.hpp"
#include "../main_menu_state/MainMenuState.hpp"
#include "../../../audio/AudioManager.hpp"
#include "../../../game/player/Player.hpp"

#include "../../../game/character/bin/DemoCharacter.hpp"
#include "../../../game/character/arcanist/Arcanist.hpp"
#include "../../../game/character/depth/Depth.hpp"
#include "../../../game/character/hero/Hero.hpp"
#include "../../../game/character/lich/Lich.hpp"
#include "../../../game/character/priestess/Priestess.hpp"
#include "../../../game/character/redhood/Redhood.hpp"
#include "../../../game/character/stormbeast/Stormbeast.hpp"
#include "../../../game/character/wyrm/Wyrm.hpp"

#include "../../../game/pattern/DemoPattern.hpp"
#include <iostream>

SoloModeState::SoloModeState(GameStateManager& gsm)
    : gameStateManager(gsm)
{
    inputInterpreters = { std::make_shared<KeyboardInputInterpreter>(), std::make_shared<KeyboardInputInterpreter>() };
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveUp, KEY_W);
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveDown, KEY_S);
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveLeft, KEY_A);
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveRight, KEY_D);

    inputInterpreters[1]->setKeyMapping(Unit::Input::Basic, KEY_ONE);
    inputInterpreters[1]->setKeyMapping(Unit::Input::Wide, KEY_TWO); 
    inputInterpreters[1]->setKeyMapping(Unit::Input::Offensive, KEY_THREE);
    inputInterpreters[1]->setKeyMapping(Unit::Input::Defensive, KEY_FOUR);

    world = std::make_unique<World>();

    std::unique_ptr<Player> player1 = std::make_unique<Player>(0, world.get(), world.get(), std::make_unique<Wyrm>(), inputInterpreters[0]);
    std::unique_ptr<Player> player2 = std::make_unique<Player>(1, world.get(), world.get(), std::make_unique<Priestess>(), inputInterpreters[1]);
    // std::unique_ptr<Player> player3 = std::make_unique<Player>(2, world.get(), world.get(), std::make_unique<Arcanist>(), inputInterpreters[1]);
    // std::unique_ptr<Player> player4 = std::make_unique<Player>(3, world.get(), world.get(), std::make_unique<Depth>(), inputInterpreters[1]);
    // std::unique_ptr<Player> player5 = std::make_unique<Player>(4, world.get(), world.get(), std::make_unique<Hero>(), inputInterpreters[1]);
    // std::unique_ptr<Player> player6 = std::make_unique<Player>(5, world.get(), world.get(), std::make_unique<Redhood>(), inputInterpreters[1]);
    // std::unique_ptr<Player> player7 = std::make_unique<Player>(6, world.get(), world.get(), std::make_unique<Stormbeast>(), inputInterpreters[1]);
    // std::unique_ptr<Player> player8 = std::make_unique<Player>(7, world.get(), world.get(), std::make_unique<Lich>(), inputInterpreters[1]);

    world->addPlayer(std::move(player1));
    world->addPlayer(std::move(player2));
    // world->addPlayer(std::move(player3));
    // world->addPlayer(std::move(player4));
    // world->addPlayer(std::move(player5));
    // world->addPlayer(std::move(player6));
    // world->addPlayer(std::move(player7));
    // world->addPlayer(std::move(player8));

    // world->addPattern(std::make_unique<DemoPattern>(world.get()));

    world->init();

    enter();
}

SoloModeState::~SoloModeState(){
    std::cout << "SoloModeState destructor called." << std::endl;
}

void SoloModeState::enter() {
    std::unique_ptr<Button> backButton = std::make_unique<Button>(
        50, 50, 300, 75, "Back to Main Menu", 50, 50, true
    );
    backButton->setOnClickListener([&gsm = gameStateManager]() {
        std::cout << "Returning to Main Menu..." << std::endl;
        gsm.changeState(std::make_unique<MainMenuState>(gsm));
        AudioManager::getInstance().play("tick");
    });
    backButton->setOnHoverEnterListener([]() {
        std::cout << "Hovered over Back button!" << std::endl;
        AudioManager::getInstance().play("tick");
    });
    buttonManager.addButton(std::move(backButton));
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