#include "NoviFire.hpp"
#include "../../../hitbox/CircleHitbox.hpp"

NoviFire::NoviFire(int id, Unit::Vec2D pos)
    : Bullet(id), pos(pos)
{
    graphics = std::make_unique<NoviFireGraphicsComponent>(this);
}

void NoviFire::update(float dt) {
    timer += dt;
    if (timer - dt < STARTUP && timer >= STARTUP) {
        pos = getPosition();
        damagingHitbox = std::make_unique<CircleHitbox>(pos, RADIUS * getSize());
    }
    if (timer > STARTUP) {
        dynamic_cast<CircleHitbox*>(damagingHitbox.get())->setRadius(getRadius());
    }
    graphics->update(dt);
}

bool NoviFire::isDone() const {
    return timer > LIFETIME;
}

Unit::Vec2D NoviFire::getPosition() const {
    return pos;
}

bool NoviFire::isStartingUp() const {
    return timer < STARTUP;
}

float NoviFire::getRadius() const {
    if (timer < STARTUP) return 0;
    float scale = std::min(BLOOM_TIME, timer - STARTUP) / BLOOM_TIME;
    return RADIUS * getSize() * scale;
}