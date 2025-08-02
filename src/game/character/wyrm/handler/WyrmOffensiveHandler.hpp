#ifndef WYRM_OFFENSIVE_HANDLER_HPP
#define WYRM_OFFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/CastHandler.hpp"

class StraightBullet;
class WyrmGraphicsComponent;
class ChargeGraphicsComponent;

class WyrmOffensiveHandler : public CastHandler {
    static constexpr float MIN_CASTING_TIME = 0.8f;
    static constexpr float MAX_CASTING_TIME = 5.0f;

    static constexpr float MIN_DURATION = 7.0f;
    static constexpr float MAX_DURATION = 14.0f;

    static constexpr float MIN_SIZEUP = 1.5f;
    static constexpr float MAX_SIZEUP = 2.4f;
    static constexpr float BULLET_MIN_SIZEUP = 1.6f;
    static constexpr float BULLET_MAX_SIZEUP = 2.7f;
    
    static constexpr float MOVEMENT_MODIFIER_VALUE = 0.66f;
    static constexpr float MOVEMENT_MODIFIER_VALUE_BURST = 1.4f;
    static constexpr float MOVEMENT_MODIFIER_DURATION_BURST = 0.8f;

    static constexpr float MIN_RADIUS = 100;
    static constexpr float MAX_RADIUS = 300;

    static constexpr float COOLDOWN = 16.0f;

public:
    WyrmOffensiveHandler(WyrmGraphicsComponent* gfx);

    void update(float dt, const InputBufferer* input) override;

protected:
    void onCastStart() override;
    void onCastRelease(bool isInterupted = false) override;

private:
    WyrmGraphicsComponent* graphics;
    
    bool isActive = false;
    float duration;
    float timer;

    StraightBullet* bulletRef = nullptr;
    ChargeGraphicsComponent* chargeGraphicsRef = nullptr;

    float getRadius() const;
};

#endif // WYRM_OFFENSIVE_HANDLER_HPP