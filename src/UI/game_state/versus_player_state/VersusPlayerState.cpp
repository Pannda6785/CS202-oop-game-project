#include "VersusPlayerState.hpp"
#include "../GameStateManager.hpp"
#include "../../../audio/AudioManager.hpp"
#include "../../button/Button.hpp"

#include "../../../game/character/priestess/Priestess.hpp"
// #include "../../../game/character/redhood/Redhood.hpp"
// #include "../../../game/character/arcanist/Arcanist.hpp"
#include "../../../game/character/hero/Hero.hpp"
#include "../../../game/character/wyrm/Wyrm.hpp"
// #include "../../../game/character/lich/Lich.hpp"
#include "../../../game/character/depth/Depth.hpp"
// #include "../../../game/character/stormbeast/Stormbeast.hpp"

#include <iostream>

VersusPlayerState::VersusPlayerState(GameStateManager& gsm)
    : gameStateManager(gsm), world(nullptr) {
}

VersusPlayerState::VersusPlayerState(GameStateManager& gsm, const std::string& player1Character, const std::string& player2Character)
    : gameStateManager(gsm), world(nullptr), player1CharacterName(player1Character), player2CharacterName(player2Character) {
    enter();
}

VersusPlayerState::~VersusPlayerState() {
}

void VersusPlayerState::enter() {
    if (!isInitialized && !player1CharacterName.empty() && !player2CharacterName.empty()) {
        initializeWorld(player1CharacterName, player2CharacterName);
    }
}

void VersusPlayerState::update(float dt) {
    if (world) {
        world->update(dt);
    }
}

void VersusPlayerState::exit() {
    // Clean up resources
    world.reset();
    inputInterpreters.clear();
    isInitialized = false;
}

void VersusPlayerState::initializeWorld(const std::string& player1Character, const std::string& player2Character) {
    // Store character names
    player1CharacterName = player1Character;
    player2CharacterName = player2Character;
    
    // Clear existing resources
    world.reset();
    inputInterpreters.clear();
    
    // Create new world
    world = std::make_unique<World>();
    
    // Create input interpreters for both players
    auto player1Input = std::make_shared<KeyboardInputInterpreter>(); // Player 1 controls
    auto player2Input = std::make_shared<KeyboardInputInterpreter>(); // Player 2 controls

    inputInterpreters.push_back(player1Input);
    inputInterpreters.push_back(player2Input);
    
    // Create characters
    auto player1Char = createCharacter(player1CharacterName);
    auto player2Char = createCharacter(player2CharacterName);
    
    // Create players and add to world
    auto player1 = std::make_unique<Player>(
        0, world.get(), world.get(), std::move(player1Char), player1Input);
    
    auto player2 = std::make_unique<Player>(
        1, world.get(), world.get(), std::move(player2Char), player2Input);
    
    // Set initial positions (facing each other)
    player1->setPosition({-10.0f, 0.0f});
    player2->setPosition({10.0f, 0.0f});
    
    // Add players to world
    world->addPlayer(std::move(player1));
    world->addPlayer(std::move(player2));
    
    // Initialize world
    world->init();
    isInitialized = true;
}

std::unique_ptr<Character> VersusPlayerState::createCharacter(const std::string& characterName) {
    if (characterName == "Sun Priestess") {
        return std::make_unique<Priestess>();
    } else if (characterName == "Hero of Frost") {
        return std::make_unique<Priestess>();
    } else {
        // Default to Sun Priestess if invalid name
        std::cerr << "Unknown character: " << characterName << ". Defaulting to Sun Priestess." << std::endl;
        return std::make_unique<Priestess>();
    }
}

void VersusPlayerState::setupUI() {
}