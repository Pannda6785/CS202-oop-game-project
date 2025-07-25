#include "StraightBulletPro.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include <algorithm>

StraightBulletPro::StraightBulletPro(int ownerId, Unit::Vec2D spawnPos, Unit::Vec2D direction, Callback speedFunc, float lifetime)
    : Bullet(ownerId), speedFunc(std::move(speedFunc)), dir(direction.normalized()), lifetime(lifetime), pos(spawnPos), timer(0.0f)
{}

void StraightBulletPro::update(float dt) {
    if (isDone()) return;

    timer += dt;

    resolvePendingHitboxes();

    // Move bullet
    Unit::Vec2D velocity = getVelocity();
    pos += velocity * dt;

    // Update hitbox positions
    if (lifeHitbox) lifeHitbox->setPosition(pos);
    if (damagingHitbox) damagingHitbox->setPosition(pos);
    if (cleansingHitbox) cleansingHitbox->setPosition(pos);
    for (auto& [hitbox, major, who, duration] : invincibilityHitboxes) {
        if (hitbox) hitbox->setPosition(pos);
    }
    for (auto& [hitbox, modifier, who, duration, amount] : modifierHitboxes) {
        if (hitbox) hitbox->setPosition(pos);
    }

    if (graphics) graphics->update(dt);
}


bool StraightBulletPro::isDone() const {
    if (timer > lifetime) return true;

    float margin = 500.0f; // a bit performance burdened, but just to be safe
    
    // check within battlefield bounds
    float minX = -margin;
    float maxX = Unit::BATTLEFIELD_WIDTH + margin;
    float minY = -margin;
    float maxY = Unit::BATTLEFIELD_HEIGHT + margin;
    if (pos.x >= minX && pos.x <= maxX &&
        pos.y >= minY && pos.y <= maxY) {
        return false;
    }

    // check if can ever re-enter
    bool movingAwayX = (pos.x < minX && dir.x <= Unit::EPS) || (pos.x > maxX && dir.x >= Unit::EPS);
    bool movingAwayY = (pos.y < minY && dir.y <= Unit::EPS) || (pos.y > maxY && dir.y >= Unit::EPS);
    if (movingAwayX || movingAwayY) return true;
    return false;
}

Unit::Vec2D StraightBulletPro::getPosition() const {
    return pos;
}

Unit::Vec2D StraightBulletPro::getVelocity() const {
    float t = timer;
    float speed = speedFunc(t);
    return dir * speed;
}

void StraightBulletPro::addBulletGraphics(std::unique_ptr<BulletGraphicsComponent> g) {
    graphics = std::move(g);
}
void StraightBulletPro::addLifeHitbox(float time, std::unique_ptr<Hitbox> hitbox) {
    pendingLifeHitbox.emplace_back(time, std::move(hitbox));
}
void StraightBulletPro::addDamagingHitbox(float time, std::unique_ptr<Hitbox> hitbox) {
    pendingDamagingHitbox.emplace_back(time, std::move(hitbox));
}
void StraightBulletPro::addCleansingHitbox(float time, std::unique_ptr<Hitbox> hitbox) {
    pendingCleansingHitbox.emplace_back(time, std::move(hitbox));
}
void StraightBulletPro::addInvincibilityHitbox(float time, std::unique_ptr<Hitbox> hitbox, bool major, int who, float duration) {
    pendingInvincibilityHitboxes.emplace_back(time, std::move(hitbox), major, who, duration);
}
void StraightBulletPro::addModifierHitbox(float time, std::unique_ptr<Hitbox> hitbox, Unit::Modifier modifier, int who, float duration, float amount) {
    pendingModifierHitboxes.emplace_back(time, std::move(hitbox), modifier, who, duration, amount);
}

void StraightBulletPro::removeLifeHitbox(float time) {
    lifeHitboxClearTime = time;
}
void StraightBulletPro::removeDamagingHitbox(float time) {
    damagingHitboxClearTime = time;
}
void StraightBulletPro::removeCleansingHitbox(float time) {
    cleansingHitboxClearTime = time;
}
void StraightBulletPro::removeInvincibilityHitboxes(float time) {
    invincibilityHitboxesClearTime = time;
}
void StraightBulletPro::removeModifierHitboxes(float time) {
    modifierHitboxesClearTime = time;
}

void StraightBulletPro::resolvePendingHitboxes() {
    // Activate scheduled hitboxes when timer >= time
    for (auto it = pendingLifeHitbox.begin(); it != pendingLifeHitbox.end();) {
        if (timer >= it->first) {
            lifeHitbox = std::move(it->second);
            it = pendingLifeHitbox.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = pendingDamagingHitbox.begin(); it != pendingDamagingHitbox.end();) {
        if (timer >= it->first) {
            damagingHitbox = std::move(it->second);
            it = pendingDamagingHitbox.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = pendingCleansingHitbox.begin(); it != pendingCleansingHitbox.end();) {
        if (timer >= it->first) {
            cleansingHitbox = std::move(it->second);
            it = pendingCleansingHitbox.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = pendingInvincibilityHitboxes.begin(); it != pendingInvincibilityHitboxes.end();) {
        if (timer >= std::get<0>(*it)) {
            invincibilityHitboxes.emplace_back(std::move(std::get<1>(*it)), std::get<2>(*it), std::get<3>(*it), std::get<4>(*it));
            it = pendingInvincibilityHitboxes.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = pendingModifierHitboxes.begin(); it != pendingModifierHitboxes.end();) {
        if (timer >= std::get<0>(*it)) {
            modifierHitboxes.emplace_back(std::move(std::get<1>(*it)), std::get<2>(*it), std::get<3>(*it), std::get<4>(*it), std::get<5>(*it));
            it = pendingModifierHitboxes.erase(it);
        } else {
            ++it;
        }
    }
    // Remove hitboxes at scheduled times
    if (lifeHitboxClearTime && timer >= *lifeHitboxClearTime) {
        lifeHitbox.reset();
        lifeHitboxClearTime = std::nullopt;
    }
    if (damagingHitboxClearTime && timer >= *damagingHitboxClearTime) {
        damagingHitbox.reset();
        damagingHitboxClearTime = std::nullopt;
    }
    if (cleansingHitboxClearTime && timer >= *cleansingHitboxClearTime) {
        cleansingHitbox.reset();
        cleansingHitboxClearTime = std::nullopt;
    }
    if (invincibilityHitboxesClearTime && timer >= *invincibilityHitboxesClearTime) {
        invincibilityHitboxes.clear();
        invincibilityHitboxesClearTime = std::nullopt;
    }
    if (modifierHitboxesClearTime && timer >= *modifierHitboxesClearTime) {
        modifierHitboxes.clear();
        modifierHitboxesClearTime = std::nullopt;
    }
}
