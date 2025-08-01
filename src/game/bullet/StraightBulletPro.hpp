#ifndef STRAIGHT_BULLET_PRO_HPP
#define STRAIGHT_BULLET_PRO_HPP

#include "Bullet.hpp"
#include "BulletGraphicsComponent.hpp"

#include <memory>
#include <functional>
#include <vector>
#include <optional>

/*
    Use this only if you do find yourself needing a bullet with the following properties:
    + Bullet is straight, with a function-defined speed
    + Bullet are deleted after a certain time or after going out of bounds.
    + Use addHitbox functions to determine when and what hitbox are drawed, if not called then the bullet has no hitbox.
    + Use addBulletGraphics to add, if not called then the bullet renders nothing.
*/

class StraightBulletPro final : public Bullet {
public:
    using Callback = std::function<float(float)>;

    StraightBulletPro(int ownerId, Unit::Vec2D spawnPos, Unit::Vec2D direction, Callback speedFunc, float lifetime);
    
    void addBulletGraphics(std::unique_ptr<BulletGraphicsComponent> graphics);

    void addLifeHitbox(float time, std::unique_ptr<Hitbox> hitbox);
    void addDamagingHitbox(float time, std::unique_ptr<Hitbox> hitbox);
    void addCleansingHitbox(float time, std::unique_ptr<Hitbox> hitbox);
    void addInvincibilityHitbox(float time, std::unique_ptr<Hitbox> hitbox, bool major, int who, float duration);
    void addModifierHitbox(float time, std::unique_ptr<Hitbox> hitbox, Unit::Modifier modifier, int who, float duration, float amount);
    void addLockHitbox(float time, std::unique_ptr<Hitbox> hitbox, Unit::Lock lock, int who, float duration);

    void removeLifeHitbox(float time);
    void removeDamagingHitbox(float time);
    void removeCleansingHitbox(float time);
    void removeInvincibilityHitboxes(float time);
    void removeModifierHitboxes(float time);
    void removeLockHitboxes(float time);

    void update(float dt) override;
    bool isDone() const override;
    void makeDone();

    Unit::Vec2D getPosition() const override;
    Unit::Vec2D getVelocity() const override;

private:
    Callback speedFunc;
    std::unique_ptr<BulletGraphicsComponent> graphics;
    Unit::Vec2D dir;
    float lifetime;
    
    Unit::Vec2D pos;
    float timer = 0.0f;
    bool forcedDone = false;

    std::vector<std::pair<float, std::unique_ptr<Hitbox>>> pendingLifeHitbox;
    std::vector<std::pair<float, std::unique_ptr<Hitbox>>> pendingDamagingHitbox;
    std::vector<std::pair<float, std::unique_ptr<Hitbox>>> pendingCleansingHitbox;
    std::vector<std::tuple<float, std::unique_ptr<Hitbox>, bool, int, float>> pendingInvincibilityHitboxes; // (time, hitbox, major, who, duration)
    std::vector<std::tuple<float, std::unique_ptr<Hitbox>, Unit::Modifier, int, float, float>> pendingModifierHitboxes; // (time, hitbox, modifier, who, duration, amount)
    std::vector<std::tuple<float, std::unique_ptr<Hitbox>, Unit::Lock, int, float>> pendingLockHitboxes; // (time, hitbox, modifier, who, duration)

    std::optional<float> lifeHitboxClearTime = std::nullopt;
    std::optional<float> damagingHitboxClearTime = std::nullopt;
    std::optional<float> cleansingHitboxClearTime = std::nullopt;
    std::optional<float> invincibilityHitboxesClearTime = std::nullopt;
    std::optional<float> modifierHitboxesClearTime = std::nullopt;
    std::optional<float> lockHitboxesClearTime = std::nullopt;

    void resolvePendingHitboxes();
};

#endif // STRAIGHT_BULLET_PRO_HPP