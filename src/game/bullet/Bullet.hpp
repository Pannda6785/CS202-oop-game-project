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
    const std::vector<std::tuple<const Hitbox*, int, float>> getInvincibilityHitboxes() const;

protected:
    int whose;
    float size = 1.0f;
    std::unique_ptr<Hitbox> lifeHitbox;
    std::unique_ptr<Hitbox> damagingHitbox;
    std::unique_ptr<Hitbox> cleansingHitbox;
    std::vector<std::tuple<std::unique_ptr<Hitbox>, int, float>> invincibilityHitboxes; // (hitbox, who, how long)
};

#endif // BULLET_HPP
