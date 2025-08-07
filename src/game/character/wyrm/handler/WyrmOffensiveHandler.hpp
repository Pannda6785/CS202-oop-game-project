#ifndef WYRM_OFFENSIVE_HANDLER_HPP
#define WYRM_OFFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/CastHandler.hpp"
#include <memory>

class StraightBullet;
class WyrmGraphicsComponent;
class ChargeGraphicsComponent;
class RippleGraphicsComponent;

class WyrmOffensiveHandler : public CastHandler {
    static constexpr float MIN_CASTING_TIME = 0.8f;
    static constexpr float MAX_CASTING_TIME = 6.5f;

    static constexpr float MIN_DURATION = 8.0f;
    static constexpr float MAX_DURATION = 17.0f;

    static constexpr float MIN_SIZEUP = 1.4f;
    static constexpr float MAX_SIZEUP = 2.2f;
    static constexpr float BULLET_MIN_SIZEUP = 1.0f;
    static constexpr float BULLET_MAX_SIZEUP = 3.0f;
    
    static constexpr float MOVEMENT_MODIFIER_VALUE_LEAST = 0.8f;
    static constexpr float MOVEMENT_MODIFIER_VALUE_GREATEST = 0.4f;
    static constexpr float MOVEMENT_MODIFIER_VALUE_BURST = 1.3f;
    static constexpr float MOVEMENT_MODIFIER_DURATION_BURST = 0.6f;

    static constexpr float MIN_RADIUS = 100;
    static constexpr float MAX_RADIUS = 300;

    static constexpr float COOLDOWN = 18.0f;

public:
    WyrmOffensiveHandler(WyrmGraphicsComponent* gfx);

    void update(float dt, const InputBufferer* input) override;

protected:
    void onCastStart() override;
    void onCastRelease(bool isInterupted = false) override;

private:
    WyrmGraphicsComponent* graphics;

    bool isActive = false;
    float timer;
    
    float duration;
    float movement_modifier;
    
    float bulletTime; // for bullet control
    std::weak_ptr<StraightBullet> bulletRef;
    ChargeGraphicsComponent* chargeGraphicsRef;
    RippleGraphicsComponent* rippleGraphicsRef;

    void recreateBullet();
    void transform(); // mere job is to change the moveset
    void detransform(); // change the moveset
    float getRadius() const;
    float getRatio() const;
};

#endif // WYRM_OFFENSIVE_HANDLER_HPP