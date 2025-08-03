#include "StraightBullet.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include <algorithm>

StraightBullet::StraightBullet(int ownerId, std::unique_ptr<BulletGraphicsComponent> graphics, Unit::Vec2D spawnPos, Unit::Vec2D direction, float speed, float lifetime)
    : Bullet(ownerId, std::move(graphics)), 
    speedFunc([speed](float) { return speed; }), dir(direction.normalized()), 
    lifetime(lifetime), pos(spawnPos), 
    timer(0.0f)
{}

StraightBullet::StraightBullet(int ownerId, std::unique_ptr<BulletGraphicsComponent> graphics, Unit::Vec2D spawnPos, Unit::Vec2D direction, Callback speedFunc, float lifetime)
    : Bullet(ownerId, std::move(graphics)), 
    speedFunc(std::move(speedFunc)), dir(direction.normalized()), 
    lifetime(lifetime), pos(spawnPos), 
    timer(0.0f)
{}

void StraightBullet::update(float dt) {
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
    for (auto& [hitbox, lock, who, duration] : lockHitboxes) {
        if (hitbox) hitbox->setPosition(pos);
    }

    if (graphics) graphics->update(dt);
}

void StraightBullet::makeDone() {
    forcedDone = true;
}

bool StraightBullet::isDone() const {
    if (timer > lifetime) return true;
    if (forcedDone) return true;

    float margin = 1000.0f;
    float minX = -margin;
    float maxX = Unit::BATTLEFIELD_WIDTH + margin;
    float minY = -margin;
    float maxY = Unit::BATTLEFIELD_HEIGHT + margin;
    if (pos.x >= minX && pos.x <= maxX &&
        pos.y >= minY && pos.y <= maxY) {
        return false;
    }

    bool movingAwayX = (pos.x < minX && dir.x <= Unit::EPS) || (pos.x > maxX && dir.x >= Unit::EPS);
    bool movingAwayY = (pos.y < minY && dir.y <= Unit::EPS) || (pos.y > maxY && dir.y >= Unit::EPS);
    if (movingAwayX || movingAwayY) return true;
    return false;
}

Unit::Vec2D StraightBullet::getPosition() const {
    return pos;
}

Unit::Vec2D StraightBullet::getVelocity() const {
    float t = timer;
    float speed = speedFunc(t);
    return dir * speed;
}

void StraightBullet::setPosition(const Unit::Vec2D& pos) {
    this->pos = pos;
    if (lifeHitbox) lifeHitbox->setPosition(pos);
    if (damagingHitbox) damagingHitbox->setPosition(pos);
    if (cleansingHitbox) cleansingHitbox->setPosition(pos);
    for (auto& [hitbox, major, who, duration] : invincibilityHitboxes) hitbox->setPosition(pos);
    for (auto& [hitbox, modifier, who, duration, amount] : modifierHitboxes) hitbox->setPosition(pos);
    for (auto& [hitbox, lock, who, duration] : lockHitboxes) hitbox->setPosition(pos);
}

void StraightBullet::addBulletGraphics(std::unique_ptr<BulletGraphicsComponent> g) {
    graphics = std::move(g);
}
void StraightBullet::addLifeHitbox(float time, std::unique_ptr<Hitbox> hitbox) {
    pendingLifeHitbox.emplace_back(time, std::move(hitbox));
}
void StraightBullet::addDamagingHitbox(float time, std::unique_ptr<Hitbox> hitbox) {
    pendingDamagingHitbox.emplace_back(time, std::move(hitbox));
}
void StraightBullet::addCleansingHitbox(float time, std::unique_ptr<Hitbox> hitbox) {
    pendingCleansingHitbox.emplace_back(time, std::move(hitbox));
}
void StraightBullet::addInvincibilityHitbox(float time, std::unique_ptr<Hitbox> hitbox, bool major, int who, float duration) {
    pendingInvincibilityHitboxes.emplace_back(time, std::move(hitbox), major, who, duration);
}
void StraightBullet::addModifierHitbox(float time, std::unique_ptr<Hitbox> hitbox, Unit::Modifier modifier, int who, float duration, float amount) {
    pendingModifierHitboxes.emplace_back(time, std::move(hitbox), modifier, who, duration, amount);
}
void StraightBullet::addLockHitbox(float time, std::unique_ptr<Hitbox> hitbox, Unit::Lock lock, int who, float duration) {
    pendingLockHitboxes.emplace_back(time, std::move(hitbox), lock, who, duration);
}

void StraightBullet::removeLifeHitbox(float time) {
    lifeHitboxClearTime = time;
}
void StraightBullet::removeDamagingHitbox(float time) {
    damagingHitboxClearTime = time;
}
void StraightBullet::removeCleansingHitbox(float time) {
    cleansingHitboxClearTime = time;
}
void StraightBullet::removeInvincibilityHitboxes(float time) {
    invincibilityHitboxesClearTime = time;
}
void StraightBullet::removeModifierHitboxes(float time) {
    modifierHitboxesClearTime = time;
}
void StraightBullet::removeLockHitboxes(float time) {
    lockHitboxesClearTime = time;
}

void StraightBullet::resolvePendingHitboxes() {
    for (auto it = pendingLifeHitbox.begin(); it != pendingLifeHitbox.end();) {
        if (timer >= it->first) {
            lifeHitbox = std::move(it->second);
            lifeHitbox->resize(getSize());
            it = pendingLifeHitbox.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = pendingDamagingHitbox.begin(); it != pendingDamagingHitbox.end();) {
        if (timer >= it->first) {
            damagingHitbox = std::move(it->second);
            damagingHitbox->resize(getSize());
            it = pendingDamagingHitbox.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = pendingCleansingHitbox.begin(); it != pendingCleansingHitbox.end();) {
        if (timer >= it->first) {
            cleansingHitbox = std::move(it->second);
            cleansingHitbox->resize(getSize());
            it = pendingCleansingHitbox.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = pendingInvincibilityHitboxes.begin(); it != pendingInvincibilityHitboxes.end();) {
        if (timer >= std::get<0>(*it)) {
            std::get<1>(*it)->resize(getSize());
            invincibilityHitboxes.emplace_back(std::move(std::get<1>(*it)), std::get<2>(*it), std::get<3>(*it), std::get<4>(*it));
            it = pendingInvincibilityHitboxes.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = pendingModifierHitboxes.begin(); it != pendingModifierHitboxes.end();) {
        if (timer >= std::get<0>(*it)) {
            std::get<1>(*it)->resize(getSize());
            modifierHitboxes.emplace_back(std::move(std::get<1>(*it)), std::get<2>(*it), std::get<3>(*it), std::get<4>(*it), std::get<5>(*it));
            it = pendingModifierHitboxes.erase(it);
        } else {
            ++it;
        }
    }
    for (auto it = pendingLockHitboxes.begin(); it != pendingLockHitboxes.end();) {
        if (timer >= std::get<0>(*it)) {
            std::get<1>(*it)->resize(getSize());
            lockHitboxes.emplace_back(std::move(std::get<1>(*it)), std::get<2>(*it), std::get<3>(*it), std::get<4>(*it));
            it = pendingLockHitboxes.erase(it);
        } else {
            ++it;
        }
    }
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
    if (lockHitboxesClearTime && timer >= *lockHitboxesClearTime) {
        lockHitboxes.clear();
        lockHitboxesClearTime = std::nullopt;
    }
}
