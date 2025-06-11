#ifndef I_PLAYER_CONTROL_HPP
#define I_PLAYER_CONTROL_HPP

#include "../../Unit.hpp"
#include <memory>
#include <array>

class IPlayerControl {
public:
    virtual ~IPlayerControl() = default;

    // Basic identity
    virtual int getPlayerId() const = 0;

    // Positional control
    virtual Unit::Vec2D getPosition() const = 0;
    virtual Unit::Vec2D getArrow() const = 0;
    virtual Unit::Vec2D getMovement() const = 0;
    virtual Unit::Vec2D getTargetPosition() const = 0;
    virtual void setPosition(const Unit::Vec2D& pos) = 0;

    // Status tracking and manipulation
    virtual float getInvincibility() const = 0;
    virtual const std::array<std::pair<float, float>, Unit::NUM_MODIFIERS>& getModifiers() const = 0;
    virtual const std::array<float, Unit::NUM_LOCKS>& getLocks() const = 0;
    virtual void applyInvincibility(float duration, bool force = false) = 0;
    virtual void applyLock(Unit::Lock lock, float duration, bool force = false) = 0;
    virtual void applyModifier(Unit::Modifier mod, float duration, float value, bool force = false) = 0;
};

#endif // I_PLAYER_CONTROL_HPP
