#ifndef BULLET_HPP
#define BULLET_HPP

#include "../../Unit.hpp"
#include "../hitbox/Hitbox.hpp"

#include <memory>

class Bullet {
public:
    Bullet(int ownerID) : whose(ownerID) {}
    virtual ~Bullet() = default;

    virtual void update(float dt) = 0;
    virtual bool isDone() const = 0;

    int isWhose() const { return whose; }
    const Hitbox* getLifeHitbox() const { return lifeHitbox.get(); }
    const Hitbox* getDamagingHitbox() const { return damagingHitbox.get(); }
    const Hitbox* getCleansingHitbox() const { return cleansingHitbox.get(); }

protected:
    int whose;
    std::unique_ptr<Hitbox> lifeHitbox;
    std::unique_ptr<Hitbox> damagingHitbox;
    std::unique_ptr<Hitbox> cleansingHitbox;

};

#endif // BULLET_HPP
