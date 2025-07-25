#ifndef WYRM_OFFENSIVE_HANDLER_HPP
#define WYRM_OFFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class WyrmGraphicsComponent;

class WyrmOffensiveHandler : public TapHandler {
    // bullet
    static constexpr float STARTUP = 0.900f;
    static constexpr float RADIUS = 9;
    static constexpr float SPEED = 720;

    static constexpr int STEP_COUNT = 4;
    static constexpr int NUM_BULLETS[STEP_COUNT] = { 3, 4, 5, 6 };
    static constexpr float BULLET_SPACING = 11; // degrees
    static constexpr float OFFSET[STEP_COUNT] = { -11, -16.5f, -22, -27.5f }; // degrees

    // move control
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.35f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.330f;
    static constexpr float ARROW_MODIFIER_AMOUNT = 0.7f;
    static constexpr float ARROW_MODIFIER_DURATION = 0.330f;
    static constexpr float SHORT_LOCK = 0.275f;
    static constexpr float LONG_LOCK = 0.650f;
    static constexpr float COMBO_HOLD = 0.650f;

public:
    WyrmOffensiveHandler(WyrmGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;
    void listen(Unit::Move move) override;

protected:
    void tap(bool isFocusing) override;

private:
    WyrmGraphicsComponent* graphics;
    int step = 0;
    float comboHold = 0.0f;

    void spawnBullet();
};

#endif // WYRM_OFFENSIVE_HANDLER_HPP