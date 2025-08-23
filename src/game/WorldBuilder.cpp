#include "WorldBuilder.hpp"
#include "./player/Player.hpp"
#include <iostream>

#include "character/priestess/Priestess.hpp"
#include "character/redhood/Redhood.hpp"
#include "character/arcanist/Arcanist.hpp"
#include "character/hero/Hero.hpp"
#include "character/wyrm/Wyrm.hpp"
#include "character/lich/Lich.hpp"
#include "character/depth/Depth.hpp"
#include "character/stormbeast/Stormbeast.hpp"

WorldBuilder::WorldBuilder(){
}

void WorldBuilder::setPlayer(int id, const std::string& characterName, const InputInterpreter* interpreter) {
    while(!(id < playerConfigs.size())) playerConfigs.push_back(PlayerConfig());
    playerConfigs[id].name = characterName;
    playerConfigs[id].interpreter = interpreter;
}

std::unique_ptr<World> WorldBuilder::getWorld() {
    auto world = std::make_unique<World>();

    for (int id = 0; id < playerConfigs.size(); ++id) {
        const auto& config = playerConfigs[id];
        std::unique_ptr<Player> player = std::make_unique<Player>(
            id,
            world.get(),
            world.get(),
            createCharacter(config.name),
            config.interpreter
        );
        world->addPlayer(std::move(player));
    }
    
    world->init();
    return world;
}

std::unique_ptr<Character> WorldBuilder::createCharacter(const std::string& characterName) {
    if (characterName == "Sun Priestess") {
        return std::make_unique<Priestess>();
    } else if (characterName == "Royal Arcanist") {
        return std::make_unique<Arcanist>();
    } else if (characterName == "Hero of Frost") {
        return std::make_unique<Hero>();
    } else if (characterName == "Dreadwyrm Heir") {
        return std::make_unique<Wyrm>();
    } else if (characterName == "Lich of Flowers") {
        return std::make_unique<Lich>();
    } else if (characterName == "Depth's Secret") {
        return std::make_unique<Depth>();
    } else if (characterName == "Stormbeast") {
        return std::make_unique<Stormbeast>();
    } else if (characterName == "Silent Redhood") {
        return std::make_unique<Redhood>();
    } else {
        std::cerr << "Unknown character: " << characterName << ". Defaulting to Sun Priestess." << std::endl;
        return std::make_unique<Priestess>();
    }
}