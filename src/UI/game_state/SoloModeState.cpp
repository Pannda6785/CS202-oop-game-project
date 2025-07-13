#include "SoloModeState.hpp"
#include <raylib.h>

SoloModeState::SoloModeState() { 
    // inputInterpreters = { std::make_shared<KeyboardInputInterpreter>(), std::make_shared<KeyboardInputInterpreter>() };
    // inputInterpreters[1]->setKeyMapping(Unit::Input::MoveUp, KEY_W);
    // inputInterpreters[1]->setKeyMapping(Unit::Input::MoveDown, KEY_S); 
    // inputInterpreters[1]->setKeyMapping(Unit::Input::MoveLeft, KEY_A);
    // inputInterpreters[1]->setKeyMapping(Unit::Input::MoveRight, KEY_D);

    // inputInterpreters[1]->setKeyMapping(Unit::Input::Basic, KEY_ONE);
    // inputInterpreters[1]->setKeyMapping(Unit::Input::Wide, KEY_TWO); 
    // inputInterpreters[1]->setKeyMapping(Unit::Input::Offensive, KEY_THREE);
    // inputInterpreters[1]->setKeyMapping(Unit::Input::Defensive, KEY_FOUR);

    // // world = std::make_unique<World>();
    // world = std::make_shared<World>();

    // std::unique_ptr<Player> player1 = std::make_unique<Player>(0, world.get(), world.get(), std::make_unique<DemoCharacter>(), inputInterpreters[0]);
    // std::unique_ptr<Player> player2 = std::make_unique<Player>(1, world.get(), world.get(), std::make_unique<DemoCharacter>(), inputInterpreters[1]);

    // world->addPlayer(std::move(player1));
    // world->addPlayer(std::move(player2));

    // world->init();
}

void SoloModeState::enter() {
}

SoloModeState::~SoloModeState() = default;

void SoloModeState::update(float dt) {
    // for (size_t i = 0; i < inputInterpreters.size(); i++)
    //     inputInterpreters[i]->update(dt); // Update input interpreters
        
    // world->update(dt); // Update game world logic
}

void SoloModeState::exit() {
}