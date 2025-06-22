#ifndef I_PLAYER_VIEW_HPP
#define I_PLAYER_VIEW_HPP

#include "../../Unit.hpp"

#include <array>

class Hitbox;

class IPlayerView {
public:
    virtual ~IPlayerView() = default;

    // Life data
    virtual int getPlayerId() const = 0;
    virtual int getHealth() const = 0;
    virtual int getStock() const = 0;

    // Positional data
    virtual const Hitbox* getHitbox() const = 0;
    virtual Unit::Vec2D getPosition() const = 0;
    virtual Unit::Vec2D getArrow() const = 0;
    virtual Unit::Vec2D getMovement() const = 0;
    virtual Unit::Vec2D getTargetPosition() const = 0;

    // Status data
    virtual float getInvincibility() const = 0;
    virtual std::pair<float, float> getModifier(Unit::Modifier mod) const = 0;
    virtual float getLock(Unit::Lock lock) const = 0;
    virtual float getCooldown(Unit::Move move) const = 0;

};

#endif // I_PLAYER_VIEW_HPP
