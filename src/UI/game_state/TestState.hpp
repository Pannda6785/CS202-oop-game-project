#ifndef TEST_STATE_HPP
#define TEST_STATE_HPP

#include "GameState.hpp"
#include "../button/ButtonManager.hpp"
#include "../button/Button.hpp"
#include <memory>

class GameStateManager;

class TestState : public GameState {
private:
    ButtonManager buttonManager;
    GameStateManager& gameStateManager;

public:
    TestState(GameStateManager& gsm);
    ~TestState();

    void enter() override;
    void update(float dt) override;
    void exit() override;
};

#endif // TEST_STATE_HPP