#ifndef I_PLAYER_CONTROL_HPP
#define I_PLAYER_CONTROL_HPP

#include "../../Unit.hpp"
#include <memory>
#include <array>

class Bullet;

class IPlayerControl {
public:
    virtual ~IPlayerControl() = default;

    // Life data
    virtual int getPlayerId() const = 0;

    // World interaction
    virtual void spawnBullet(std::unique_ptr<Bullet> bullet) = 0;

    // Positional control
    virtual Unit::Vec2D getPosition() const = 0;
    virtual Unit::Vec2D getArrow() const = 0;
    virtual Unit::Vec2D getMovement() const = 0;
    virtual Unit::Vec2D getTargetPosition() const = 0;
    virtual void setPosition(const Unit::Vec2D& pos) = 0;

    // Status tracking and manipulation
    virtual float getInvincibility() const = 0;
    virtual std::pair<float, float> getModifier(Unit::Modifier mod) const = 0;
    virtual float getLock(Unit::Lock lock) const = 0;
    virtual float getCooldown(Unit::Move move) const = 0;

    virtual void applyInvincibility(float duration, bool force = false) = 0;
    virtual void applyModifier(Unit::Modifier mod, float duration, float value, bool force = false) = 0;
    virtual void applyLock(Unit::Lock lock, float duration, bool force = false) = 0;
    virtual void applyCooldown(Unit::Move move, float duration, bool force = false) = 0;
};

#endif // I_PLAYER_CONTROL_HPP
