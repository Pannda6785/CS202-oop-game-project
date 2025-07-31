#ifndef DEPTH_OFFENSIVE_HANDLER_HPP
#define DEPTH_OFFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/HoldHandler.hpp"

class DepthGraphicsComponent;

class DepthOffensiveHandler : public HoldHandler {
    // bullet
    static constexpr float STARTUP = 0.180f;
    static constexpr float RADIUS = 50;
    static constexpr float SPEED_FAST = 14.5f * 60;
    static constexpr float SPEED_SLOW = 4.0f * 60;
    static constexpr int NUM_STEPS = 4;
    static constexpr float FAST_DURATION[NUM_STEPS] = { 0.5f, 0.7f, 0.9f, 1.1f };
    static constexpr float SLOW_DURATION = 0.700f; // life time is fast + slow
    static constexpr int NUM_BULLETS = 7;
    static constexpr float ANGLE_SPREAD[NUM_STEPS] = { 30, 25, 20, 15 }; // bullets spread evenly in [-x, x] degrees

    // move control
    static constexpr float COOLDOWN = 3.500f;
    static constexpr float MOVEMENT_MODIFIER_VALUE = 0.15f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.720f;
    static constexpr float SPELL_LOCK = 0.680f;
    static constexpr float ARROW_LOCK = 1.280f;
    static constexpr float COMBO_HOLD = 1.240f; // also a cooldown hold

public:
    DepthOffensiveHandler(DepthGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;
    void listen(Unit::Move move) override;

protected:
    void tick(bool isFocusing) override;

private:
    DepthGraphicsComponent* graphics;
    int step = 0;
    float comboHold = 0.0f;

    void spawnBullet();

};

#endif // DEPTH_OFFENSIVE_HANDLER_HPP