#ifndef DEMO_BULLET_H
#define DEMO_BULLET_H

#include "Bullet.h"
#include "CircleHitbox.h"
#include <cmath>
#include <raylib.h>

class DemoBullet : public Bullet {
public:
    DemoBullet(int ownerId, const Unit::Vec2D& spawnPos, const Unit::Vec2D& direction, float speed, float lifetime)
        : position(spawnPos), remainingLife(lifetime)
    {
        whose = ownerId;

        // Normalize direction
        float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        Unit::Vec2D dir = (len > 0.0f) ? Unit::Vec2D{ direction.x / len, direction.y / len } : Unit::Vec2D{0, 0};

        velocity = { dir.x * speed, dir.y * speed };

        float radius = 8.0f;
        damagingHitbox = std::make_unique<CircleHitbox>(spawnPos, radius);
        lifeHitbox     = std::make_unique<CircleHitbox>(spawnPos, radius);
    }

    void update(float dt) override {
        remainingLife -= dt;
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        if (damagingHitbox) damagingHitbox->setPosition(position);
        if (lifeHitbox) lifeHitbox->setPosition(position);
    }

    bool isDone() const override {
        return remainingLife <= 0.0f;
    }

    void render(Renderer& renderer) const override {
        DrawCircleV({position.x, position.y}, 8.0f, {255, 0, 0, 255});
    }

private:
    Unit::Vec2D position;
    Unit::Vec2D velocity;
    float remainingLife;
};

#endif // DEMO_BULLET_H
