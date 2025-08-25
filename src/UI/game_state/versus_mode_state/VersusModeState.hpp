#ifndef VERSUS_PLAYER_STATE_HPP
#define VERSUS_PLAYER_STATE_HPP

#include "../GameState.hpp"
#include "../../../input/InputInterpreter.hpp"
#include "../../../game/World.hpp"
#include "../../../game/player/Player.hpp"
#include "../../button/ButtonManager.hpp"
#include <memory>
#include <vector>
#include <string>

class GameStateManager; // Forward declaration

enum class PostGameOption;

class VersusModeState : public GameState {
public:
    VersusModeState(GameStateManager& gsm, std::unique_ptr<World> world, std::vector<std::shared_ptr<InputInterpreter>> interpreters);
    ~VersusModeState() override;

    void enter() override;
    void update(float dt) override;
    void exit() override;
    
private:
    GameStateManager& gameStateManager;
    std::unique_ptr<World> world = nullptr;
    std::vector<std::shared_ptr<InputInterpreter>> interpreters;
    PostGameOption selectedOption;
};

#endif // VERSUS_MODE_STATE_HPP