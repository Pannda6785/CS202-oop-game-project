#ifndef I_PLAYER_VIEW_HPP
#define I_PLAYER_VIEW_HPP

#include "../../Unit.hpp"

#include <array>

class CircleHitbox;

class IPlayerView {
public:
    virtual ~IPlayerView() = default;

    // Life data
    virtual int getPlayerId() const = 0;
    virtual int getHealth() const = 0;
    virtual int getStock() const = 0;

    // Positional data
    virtual const CircleHitbox* getHitbox() const = 0;
    virtual Unit::Vec2D getPosition() const = 0;
    virtual Unit::Vec2D getArrow() const = 0;
    virtual Unit::Vec2D getMovement() const = 0;
    virtual Unit::Vec2D getTargetPosition() const = 0;

    // Status data
    virtual float getInvincibility() const = 0;
    virtual const std::array<std::pair<float, float>, Unit::NUM_MODIFIERS>& getModifiers() const = 0;
    virtual const std::array<float, Unit::NUM_LOCKS>& getLocks() const = 0;

    // Character data

};

#endif // I_PLAYER_VIEW_HPP
