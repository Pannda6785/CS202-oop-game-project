#ifndef IPLAYERFORCHARACTER_H
#define IPLAYERFORCHARACTER_H

#include "GameUnits.h"
#include <memory>

class Bullet;

class IPlayerForCharacter {
public:
    virtual ~IPlayerForCharacter() = default;

    virtual int getId() const = 0;
    virtual Unit::Vec2D getPosition() const = 0;
    virtual Unit::Vec2D getArrow() const = 0;
    virtual const std::array<float, Unit::NUM_MOVES>& getCooldown() const = 0;
    virtual const std::array<float, Unit::NUM_STATUS_EFFECTS>& getStatusEffects() const = 0;
    virtual const std::array<float, Unit::NUM_LOCKS>& getLocks() const = 0;

    virtual void spawnBullet(std::unique_ptr<Bullet> bullet) = 0;

    virtual void setPosition(const Unit::Vec2D& pos) = 0;
    virtual void applyCooldown(Unit::Move, float duration) = 0;
    virtual void applyStatusEffect(Unit::StatusEffect effect, float duration) = 0;
    virtual void applyLock(Unit::Modifier mod, float duration) = 0;
    virtual void applyModifier(Unit::Modifier mod, float duration, float value) = 0;
};

#endif // IPLAYERFORCHARACTER_H
