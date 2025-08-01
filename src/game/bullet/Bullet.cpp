#include "Bullet.hpp"

Bullet::Bullet(int ownerID, std::unique_ptr<BulletGraphicsComponent> graphics) : whose(ownerID), graphics(std::move(graphics)) {
    this->graphics->registerBullet(this);
}

BulletGraphicsComponent* Bullet::getGraphics() const {
    return graphics.get();
}

int Bullet::isWhose() const {
    return whose;
}

Unit::Vec2D Bullet::getPosition() const {
    std::cerr << "Warning: Bullet::getPosition() is not overriden, are you sure?" << std::endl;
    if (lifeHitbox) return lifeHitbox->getPosition();
    if (damagingHitbox) return damagingHitbox->getPosition();
    if (cleansingHitbox) return cleansingHitbox->getPosition();
    std::cerr << "Warning: Bullet::getPosition() called without any hitbox set." << std::endl;
    return {0.0f, 0.0f};
}

Unit::Vec2D Bullet::getVelocity() const {
    std::cerr << "Warning: Bullet::getVelocity() is not overriden!" << std::endl;
    return {0.0f, 0.0f};
}

float Bullet::getSize() const {
    return size;
}

void Bullet::resize(float scale) {
    size *= scale;
    if (lifeHitbox) lifeHitbox->resize(scale);
    if (damagingHitbox) damagingHitbox->resize(scale);
    if (cleansingHitbox) cleansingHitbox->resize(scale);
    for (auto& [hitbox, major, who, duration] : invincibilityHitboxes) hitbox->resize(scale);
    for (auto& [hitbox, modifier, who, duration, amount] : modifierHitboxes) hitbox->resize(scale);
    for (auto& [hitbox, lock, who, duration] : lockHitboxes) hitbox->resize(scale);
}

const Hitbox* Bullet::getLifeHitbox() const {
    return lifeHitbox.get();
}

const Hitbox* Bullet::getDamagingHitbox() const {
    return damagingHitbox.get();
}

const Hitbox* Bullet::getCleansingHitbox() const {
    return cleansingHitbox.get();
}

const std::vector<std::tuple<const Hitbox*, bool, int, float>> Bullet::getInvincibilityHitboxes() const {
    std::vector<std::tuple<const Hitbox*, bool, int, float>> result;
    for (const auto& [hitbox, major, who, duration] : invincibilityHitboxes) {
        result.emplace_back(hitbox.get(), major, who, duration);
    }
    return result;
}

const std::vector<std::tuple<const Hitbox*, Unit::Modifier, int, float, float>> Bullet::getModifierHitboxes() const {
    std::vector<std::tuple<const Hitbox*, Unit::Modifier, int, float, float>> result;
    for (const auto& [hitbox, modifier, who, duration, amount] : modifierHitboxes) {
        result.emplace_back(hitbox.get(), modifier, who, duration, amount);
    }
    return result;
}

const std::vector<std::tuple<const Hitbox*, Unit::Lock, int, float>> Bullet::getLockHitboxes() const {
    std::vector<std::tuple<const Hitbox*, Unit::Lock, int, float>> result;
    for (const auto& [hitbox, modifier, who, duration] : lockHitboxes) {
        result.emplace_back(hitbox.get(), modifier, who, duration);
    }
    return result;
}