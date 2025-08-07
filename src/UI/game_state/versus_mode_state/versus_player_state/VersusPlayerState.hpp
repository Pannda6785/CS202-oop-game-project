#ifndef VERSUS_PLAYER_STATE_HPP
#define VERSUS_PLAYER_STATE_HPP

#include "../../GameState.hpp"
#include "../../../../input/InputInterpreter.hpp"
#include "../../../../input/KeyboardInputInterpreter.hpp"
#include "../../../../game/World.hpp"
#include "../../../../game/player/Player.hpp"
#include "../../../button/ButtonManager.hpp"
#include <memory>
#include <vector>
#include <string>

class GameStateManager; // Forward declaration

class VersusPlayerState : public GameState {
public:
    VersusPlayerState(GameStateManager& gsm);
    VersusPlayerState(GameStateManager& gsm, const std::string& player1Character, const std::string& player2Character);
    ~VersusPlayerState() override;

    void enter() override;
    void update(float dt) override;
    void exit() override;
    
    // Initialize world with specified characters
    void initializeWorld(const std::string& player1Character, const std::string& player2Character);

private:
    GameStateManager& gameStateManager;
    std::unique_ptr<World> world = nullptr;
    std::vector<std::shared_ptr<KeyboardInputInterpreter>> inputInterpreters;
    ButtonManager buttonManager;
    
    std::string player1CharacterName;
    std::string player2CharacterName;
    bool isInitialized = false;
    
    std::unique_ptr<Character> createCharacter(const std::string& characterName);
    void setupUI();
};

#endif // VERSUS_PLAYER_STATE_HPP