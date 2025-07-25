#ifndef NOVI_FIRE_HPP
#define NOVI_FIRE_HPP

#include "../../../bullet/Bullet.hpp"
#include "NoviFireGraphicsComponent.hpp"

#include <memory>

class NoviFire final : public Bullet {
    static constexpr float STARTUP = 0.780f;
    static constexpr float RADIUS = 462;
    static constexpr float LIFETIME = STARTUP + 0.4f;
    static constexpr float BLOOM_TIME = 0.1f;

public:
    NoviFire(int id, Unit::Vec2D pos);

    void update(float dt) override;
    bool isDone() const override;

    Unit::Vec2D getPosition() const override;

    bool isStartingUp() const;
    float getRadius() const;

private:
    std::unique_ptr<NoviFireGraphicsComponent> graphics;

    Unit::Vec2D pos;
    float timer = 0;
};

#endif // NOVI_FIRE_HPP