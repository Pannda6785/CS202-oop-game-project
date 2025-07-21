#ifndef BULLET_HPP
#define BULLET_HPP

#include "../../Unit.hpp"
#include "../hitbox/Hitbox.hpp"

#include <memory>
#include <vector>

class Bullet {
public:
    explicit Bullet(int ownerID);
    virtual ~Bullet() = default;

    virtual void update(float dt) = 0;
    virtual bool isDone() const = 0;

    virtual Unit::Vec2D getPosition() const;
    virtual Unit::Vec2D getVelocity() const;
    
    int isWhose() const;
    float getSize() const;
    virtual void resize(float scale);

    const Hitbox* getLifeHitbox() const;
    const Hitbox* getDamagingHitbox() const;
    const Hitbox* getCleansingHitbox() const;
    const std::vector<std::tuple<const Hitbox*, bool, int, float>> getInvincibilityHitboxes() const;
    const std::vector<std::tuple<const Hitbox*, Unit::Modifier, int, float, float>> getModifierHitboxes() const;

protected:
    int whose;
    float size = 1.0f;
    std::unique_ptr<Hitbox> lifeHitbox;
    std::unique_ptr<Hitbox> damagingHitbox;
    std::unique_ptr<Hitbox> cleansingHitbox;
    std::vector<std::tuple<std::unique_ptr<Hitbox>, bool, int, float>> invincibilityHitboxes; // (hitbox, major, who, how long)
    std::vector<std::tuple<std::unique_ptr<Hitbox>, Unit::Modifier, int, float, float>> modifierHitboxes; // (hitbox, which modifier, who, how long, how much)
};

#endif // BULLET_HPP
