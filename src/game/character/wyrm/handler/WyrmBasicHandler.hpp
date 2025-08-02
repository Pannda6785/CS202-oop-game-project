#ifndef WYRM_BASIC_HANDLER_HPP
#define WYRM_BASIC_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class WyrmGraphicsComponent;

class WyrmBasicHandler : public TapHandler {
    // bullet
    static constexpr float STARTUP = 0.180f;
    static constexpr float RADIUS = 9;
    static constexpr float SPEED = 720;

    static constexpr int STEP_COUNT = 4;
    static constexpr int NUM_BULLETS[STEP_COUNT] = { 3, 4, 5, 6 };
    static constexpr float BULLET_SPACING = 11; // degrees
    static constexpr float OFFSET[STEP_COUNT] = { -11, -16.5f, -22, -27.5f }; // degrees, the first bullet, increment by spacing each

    // move control
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.35f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.300f;
    static constexpr float ARROW_MODIFIER_AMOUNT = 0.7f;
    static constexpr float ARROW_MODIFIER_DURATION = 0.300f;
    static constexpr float SHORT_LOCK = 0.240f;
    static constexpr float LONG_LOCK = 0.650f;
    static constexpr float COMBO_HOLD = 0.640f;

public:
    WyrmBasicHandler(WyrmGraphicsComponent* graphics);

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

#endif // WYRM_BASIC_HANDLER_HPP
