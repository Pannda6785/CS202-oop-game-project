#ifndef STRAIGHT_BULLET_HPP
#define STRAIGHT_BULLET_HPP

#include "Bullet.hpp"
#include "BulletGraphicsComponent.hpp"

#include <memory>
#include <functional>
#include <vector>
#include <string>
#include <optional>

/*
    Use this only if you do find yourself needing a bullet with the following properties:
    + Bullet is straight, with a function-defined speed
    + Bullet are deleted after a certain time or after going out of bounds.
    + Use addHitbox functions to determine when and what hitbox are drawed, if not called then the bullet has no hitbox.
    + Use addBulletGraphics to add, if not called then the bullet renders nothing.
*/

class StraightBullet final : public Bullet {
public:
    using Callback = std::function<float(float)>;

    StraightBullet(int ownerId, std::unique_ptr<BulletGraphicsComponent> graphics, Unit::Vec2D spawnPos, Unit::Vec2D direction, float speed, float lifetime);
    StraightBullet(int ownerId, std::unique_ptr<BulletGraphicsComponent> graphics, Unit::Vec2D spawnPos, Unit::Vec2D direction, Callback speedFunc, float lifetime);

    void addBulletGraphics(std::unique_ptr<BulletGraphicsComponent> g);
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

    void addStartupSound(std::string name, float early = 0.0f);

    void update(float dt) override;
    bool isDone() const override;
    void makeDone() override;

    Unit::Vec2D getPosition() const override;
    Unit::Vec2D getVelocity() const override;
    void setPosition(const Unit::Vec2D& pos);

private:
    // bullet constant info
    Callback speedFunc;
    Unit::Vec2D dir;
    float lifetime;
    
    // tracking fields
    Unit::Vec2D pos;
    float timer = 0.0f;
    bool madeDone = false;
    float whenMadeDone;
    const float howLongAfterMadeDone = 0.18f;

    // hitboxes trackers
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

    bool isStartedUp;
    std::vector<std::string> startupSounds;
    float earlyStartupTime;

    void resolvePendingHitboxes();
    void playStartupSound();
};

#endif // STRAIGHT_BULLET_HPP