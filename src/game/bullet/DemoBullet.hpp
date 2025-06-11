#ifndef DEMO_BULLET_HPP
#define DEMO_BULLET_HPP

#include "Bullet.hpp"

class DemoBullet : public Bullet {
public:
    DemoBullet(int ownerId, const Unit::Vec2D& spawnPos, const Unit::Vec2D& direction, float radius, float speed, float lifetime);

    void update(float dt) override;
    bool isDone() const override;

private:
    Unit::Vec2D position;
    Unit::Vec2D velocity;
    float remainingLife;
};

#endif // DEMO_BULLET_HPP
