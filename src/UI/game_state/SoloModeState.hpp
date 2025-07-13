#ifndef SOLO_MODE_STATE_HPP
#define SOLO_MODE_STATE_HPP

#include "GameState.hpp"
#include "../../input/InputInterpreter.hpp"
#include "../../input/KeyboardInputInterpreter.hpp"

#include "../../game/World.hpp"
#include "../../game/player/Player.hpp"

#include "../../game/character/DemoCharacter.hpp"
#include <memory>
#include <vector>

class SoloModeState : public GameState {
public:
    SoloModeState();
    ~SoloModeState() override;

    void enter() override;
    void update(float dt) override;
    void exit() override;
    
private:
    // std::unique_ptr<World> world;
    std::shared_ptr<World> world;
    std::vector<std::shared_ptr<KeyboardInputInterpreter>> inputInterpreters;
    // Add more members if needed (e.g., UI overlays, pause state, etc.)
};

#endif // SOLO_MODE_STATE_HPP