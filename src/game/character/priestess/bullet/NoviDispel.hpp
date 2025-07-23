#ifndef NOVI_DISPEL_HPP
#define NOVI_DISPEL_HPP

#include "../../../bullet/Bullet.hpp"
#include "NoviDispelGraphicsComponent.hpp"

class NoviDispel : public Bullet {
    static constexpr float BASE_RADIUS = 480.0f;
    static constexpr float CLEANSE_RADIUS = BASE_RADIUS * 0.92f;
    static constexpr float ACTIVE_TIME = 1.5f;
    static constexpr float INVINCIBILITY_DURATION = 0.5f; // each tick apply this

    int frame = 0;
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.25f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 1.5f;

public:
    NoviDispel(int id, Unit::Vec2D pos);

    void update(float dt) override;
    bool isDone() const override;

private:
    std::unique_ptr<NoviDispelGraphicsComponent> graphics;
    float timeLeft;
    
};

#endif // NOVI_DISPEL_HPP
