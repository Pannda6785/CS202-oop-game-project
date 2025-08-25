#include "WorldBuilder.hpp"
#include "./player/Player.hpp"
#include "../game/ai/GeneralAIInterpreter.hpp"

#include <iostream>

#include "character/priestess/Priestess.hpp"
#include "character/redhood/Redhood.hpp"
#include "character/arcanist/Arcanist.hpp"
#include "character/hero/Hero.hpp"
#include "character/wyrm/Wyrm.hpp"
#include "character/lich/Lich.hpp"
#include "character/depth/Depth.hpp"
#include "character/stormbeast/Stormbeast.hpp"

#include "challenge/BomblessMaiden.hpp"
#include "challenge/GiantMaiden.hpp"
#include "challenge/IronMaiden.hpp"
#include "challenge/StoneHeartPulsation.hpp"
#include "challenge/StoneStaticGreen.hpp"
#include "challenge/TimeskipMaiden.hpp"

WorldBuilder::WorldBuilder(bool isVsPlayer) : isVsPlayer(isVsPlayer) {
    world = std::make_unique<World>();
}

void WorldBuilder::setPlayer(int id, const std::string& characterName, std::shared_ptr<InputInterpreter> interpreter) {
    while(!(id < playerConfigs.size())) playerConfigs.push_back(PlayerConfig());
    playerConfigs[id].name = characterName;
    playerConfigs[id].interpreter = interpreter;
}

void WorldBuilder::setAI(int id, const std::string& characterName) {
    while(!(id < playerConfigs.size())) playerConfigs.push_back(PlayerConfig());
    playerConfigs[id].name = characterName;
    playerConfigs[id].interpreter = std::make_shared<GeneralAIInterpreter>(world.get(), 1);
}

void WorldBuilder::setChallenge(const std::string& challengeName) {
    int index = -1;
    auto availableChallenges = getAvailableChallenges();
    for(int i = 0; i < availableChallenges.size(); i++) {
        if(availableChallenges[i] == challengeName) {
            index = i;
            break;
        }
    }
    if(index != -1){
        challengeFlags[index] = !challengeFlags[index];
    }
}

std::array<bool, 6> WorldBuilder::getChallengeFlags() const {
    return challengeFlags;
}

std::unique_ptr<World> WorldBuilder::getWorld() {
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
    for (int i = 0; i < challengeFlags.size(); ++i) {
        if (challengeFlags[i]) {
            world->addChallenge(createChallenge(getAvailableChallenges()[i]));
        }
    }
    world->init();
    return std::move(world);
}

std::vector<std::shared_ptr<InputInterpreter>> WorldBuilder::getInterpreters() const {
    std::vector<std::shared_ptr<InputInterpreter>> interpreters;
    for (const auto& config : playerConfigs) {
        if (config.interpreter) {
            interpreters.push_back(config.interpreter);
        }
    }
    return interpreters;
}

std::vector<std::string> WorldBuilder::getAvailableChallenges() const {
    return {
        "Bombless Maiden",
        "Giant Maiden",
        "Iron Maiden",
        "Stone Heart Pulsation",
        "Stone Static Green",
        "Timeskip Maiden"
    };
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

std::unique_ptr<Challenge> WorldBuilder::createChallenge(const std::string& challengeName) {
    if (challengeName == "Bombless Maiden") {
        return std::make_unique<BomblessMaiden>();
    } else if (challengeName == "Giant Maiden") {
        return std::make_unique<GiantMaiden>();
    } else if (challengeName == "Iron Maiden") {
        return std::make_unique<IronMaiden>();
    } else if (challengeName == "Stone Heart Pulsation") {
        return std::make_unique<StoneHeartPulsation>();
    } else if (challengeName == "Stone Static Green") {
        return std::make_unique<StoneStaticGreen>();
    } else if (challengeName == "Timeskip Maiden") {
        return std::make_unique<TimeskipMaiden>();
    } else {
        std::cerr << "Unknown challenge: " << challengeName << std::endl;
        return nullptr;
    }
}