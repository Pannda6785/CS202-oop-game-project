#ifndef BULLET_H
#define BULLET_H

#include "GameUnits.h"
#include "Renderer.h"
#include "Hitbox.h"
// #include "BulletGraphicsComponent.h"

#include <memory>
#include <vector>
#include <tuple>

class Bullet {
public:
    virtual ~Bullet() = default;

    virtual void update(float dt) = 0;
    virtual bool isDone() const = 0;
    virtual void render(Renderer& renderer) const = 0;

    int isWhose() const { return whose; }
    const Hitbox* getLifeHitbox() const { return lifeHitbox.get(); }
    const Hitbox* getDamagingHitbox() const { return damagingHitbox.get(); }
    const Hitbox* getCleansingHitbox() const { return cleansingHitbox.get(); }
    const std::vector<std::tuple<std::unique_ptr<Hitbox>, Unit::StatusEffect, float, int>>& getStatusEffectHitboxes() const { return statusEffectHitboxes; }

protected:
    int whose;
    std::unique_ptr<Hitbox> lifeHitbox;
    std::unique_ptr<Hitbox> damagingHitbox;
    std::unique_ptr<Hitbox> cleansingHitbox;
    std::vector<std::tuple<std::unique_ptr<Hitbox>, Unit::StatusEffect, float, int>> statusEffectHitboxes; // (hitbox, effect, to whom)
};

#endif // BULLET_H
