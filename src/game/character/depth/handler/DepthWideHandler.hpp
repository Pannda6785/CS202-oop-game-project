#ifndef DEPTH_WIDE_HANDLER_HPP
#define DEPTH_WIDE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class DepthGraphicsComponent;

class DepthWideHandler : public TapHandler {
    // bullet
    static constexpr float STARTUP = 0.330f;
    static constexpr float RADIUS = 37.5f;
    static constexpr float SPEED_IN = 210;
    static constexpr float SPEED_OUT = 300;
    static constexpr float SPAWN_RADIUS = 150; // where to spawn
    static constexpr int NUM_BULLETS = 12;

    // move control
    static constexpr float MOVEMENT_LOCK = 0.080f;
    static constexpr float ARROW_LOCK = 0.080f;
    static constexpr float ATTACK_LOCK = 1.180f;

public:
    DepthWideHandler(DepthGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    DepthGraphicsComponent* graphics;

    void spawnBullet();
};

#endif // DEPTH_WIDE_HANDLER_HPP