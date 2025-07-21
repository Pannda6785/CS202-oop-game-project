#ifndef SOLO_MODE_STATE_HPP
#define SOLO_MODE_STATE_HPP

#include "../GameState.hpp"
#include "../../../input/InputInterpreter.hpp"
#include "../../../input/KeyboardInputInterpreter.hpp"
#include "../../../game/World.hpp"
#include "../../../game/player/Player.hpp"
#include "../../../game/character/DemoCharacter.hpp"
#include "../../button/ButtonManager.hpp"
#include <memory>
#include <vector>

class GameStateManager; // Forward declaration

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
    std::vector<std::shared_ptr<KeyboardInputInterpreter>> inputInterpreters;
    ButtonManager buttonManager;
};

#endif // SOLO_MODE_STATE_HPP