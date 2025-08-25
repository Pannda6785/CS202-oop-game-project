#ifndef SOLO_MODE_STATE_HPP
#define SOLO_MODE_STATE_HPP

#include "../GameState.hpp"
#include "../../../input/InputInterpreter.hpp"
#include "../../../input/KeyboardInputInterpreter.hpp"
#include "../../../game/World.hpp"
#include "../../../game/player/Player.hpp"
#include "../../button/ButtonManager.hpp"
#include <memory>
#include <vector>

class GameStateManager; // Forward declaration

enum class PostGameOption;

class SoloModeState : public GameState {
public:
    SoloModeState(GameStateManager& gsm);
    ~SoloModeState() override;

    void enter() override;
    void update(float dt) override;
    void exit() override;

private:
    GameStateManager& gameStateManager;
    std::unique_ptr<World> world;
    PostGameOption selectedOption;
};

#endif // SOLO_MODE_STATE_HPP