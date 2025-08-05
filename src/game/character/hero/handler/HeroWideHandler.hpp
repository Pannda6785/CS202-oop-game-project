#ifndef HERO_WIDE_HANDLER_HPP
#define HERO_WIDE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class HeroGraphicsComponent;

class HeroWideHandler : public TapHandler {
    static constexpr float DELAY = 0.300f;
    static constexpr float STARTUP = 0.180f;
    static constexpr float RADIUS = 16;
    static constexpr float SPEED_INIT = 1200;
    static constexpr float SPEED_FINAL = 300;
    static constexpr float LIFETIME = 0.750f;
    static constexpr float FADEOUT = 0.150f;

    static constexpr float MOVEMENT_MODIFIER_VALUE = 0.85f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.800f;
    static constexpr float ATTACK_LOCK = 1.000f;

public:
    HeroWideHandler(HeroGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;

protected:
    void tap(bool isFocusing) override;

private:
    HeroGraphicsComponent* graphics;

    float timer;
    Unit::Vec2D directionSnapshot;

    void spawnBullet(float angle);

};

#endif // HERO_WIDE_HANDLER_HPP