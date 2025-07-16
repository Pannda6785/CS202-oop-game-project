#include "Sunburst.hpp"

#include "../../../hitbox/CircleHitbox.hpp"

Sunburst::Sunburst(int id, Unit::Vec2D pos, Unit::Vec2D arrow, Unit::Vec2D target, bool focused)
    : Bullet(id), pos(pos), focused(focused) {

    vel = arrow * SPEED;
    toTravel = arrow.dot(target - pos);
    if (focused) {
        toTravel = std::max(0.0f, toTravel - FOCUS_DISTANCE_SHORTENING);
        startupTime = FOCUS_STARTUP;
    } else {
        startupTime = BASE_STARTUP;
    }
    activeTime = ACTIVE_TIME;
    bloomTime = BLOOM_TIME;
    startedup = false;

    graphics = std::make_unique<SunburstGraphicsComponent>(this);
}

void Sunburst::update(float dt) {
    if (graphics) {
        graphics->update(dt);
    }
    if (toTravel > Unit::EPS) { // still traveling
        float d = toTravel / SPEED;
        d = std::min(d, dt);
        pos += vel * d;
        toTravel -= SPEED * d;
        return;
    }
    if (startupTime > Unit::EPS) { // still (additional) starting up
        startupTime -= dt; startupTime;
        return;
    }
    if (!startedup) { // trigger the startup
        startedup = true;
        damagingHitbox = std::make_unique<CircleHitbox>(pos, getRadius());
    }
    if (bloomTime > Unit::EPS) { // waiting to bloom
        float d = std::min(dt, bloomTime);
        bloomTime -= d;
        dynamic_cast<CircleHitbox*>(damagingHitbox.get())->setRadius(getRadius());
    }
    if (activeTime > Unit::EPS) { // waiting to die out
        activeTime -= dt;
        return;
    }
}

bool Sunburst::isDone() const {
    return activeTime < Unit::EPS;
}

Unit::Vec2D Sunburst::getPosition() const {
    return pos;
}

bool Sunburst::isStartingUp() const {
    return !startedup;
}

bool Sunburst::isFocused() const {
    return focused;
}

float Sunburst::getRadius() const {
    if (!startedup) {
        return 0;
    } else {
        return (BASE_RADIUS - BASE_RADIUS * pow(bloomTime / (BLOOM_TIME * 2.2f), 1.8f)) * getSize();
    }
}   

float Sunburst::getRingRadius() const {
    return BASE_RADIUS * getSize();
}