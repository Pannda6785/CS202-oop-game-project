#include "Bullet.hpp"

Bullet::Bullet(int ownerID) : whose(ownerID) {}

int Bullet::isWhose() const {
    return whose;
}

Unit::Vec2D Bullet::getPosition() const {
    if (lifeHitbox) return lifeHitbox->getPosition();
    if (damagingHitbox) return damagingHitbox->getPosition();
    if (cleansingHitbox) return cleansingHitbox->getPosition();
    std::cerr << "Bullet::getPosition() called without any hitbox set." << std::endl;
    return {0.0f, 0.0f};
}

Unit::Vec2D Bullet::getVelocity() const {
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

const std::vector<std::tuple<Hitbox*, int, float>> Bullet::getInvincibilityHitboxes() const {
    std::vector<std::tuple<Hitbox*, int, float>> result;
    for (const auto& [hitbox, who, duration] : invincibilityHitboxes) {
        result.emplace_back(hitbox.get(), who, duration);
    }
    return result;
}
