#ifndef DEPTH_DEFENSIVE_HANDLER_HPP
#define DEPTH_DEFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/CastHandler.hpp"
#include <memory>

class DepthGraphicsComponent;
class StraightBullet;
class ChargeGraphicsComponent;

class DepthDefensiveHandler : public CastHandler {
    static constexpr float MIN_CASTING_TIME = 0.1f;
    static constexpr float MAX_CASTING_TIME = 1;
    static constexpr float MOVEMENT_MODIFIER_CAST = 0.2f;

    static constexpr float INVINCIBILITY_DURATION_MIN = 0.820f;
    static constexpr float INVINCIBILITY_DURATION_MAX = 0.880f;

    static constexpr float SPAWN_DISTANCE = 100.0f;
    static constexpr float MIN_RADIUS = 166;
    static constexpr float MAX_RADIUS = 222;
    static constexpr float SPEED = 720;
    static constexpr float STARTUP = 0.380f;
    static constexpr float CLEANSE_RADIUS_RATIO = 0.96f;
    
    static constexpr float COOLDOWN = 7.0f;
    static constexpr float SPELL_LOCK = 0.480f;
    static constexpr float MOVEMENT_MODIFIER_VALUE = 1.1;
    static constexpr float MOVEMENT_MODIFIER_DURATION_MIN = 0.820f;
    static constexpr float MOVEMENT_MODIFIER_DURATION_MAX = 0.880f;

public:
    DepthDefensiveHandler(DepthGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;

protected:
    void onCastStart() override;
    void onCastRelease(bool isInterupted = false) override;

private:
    DepthGraphicsComponent* graphics;

    std::weak_ptr<StraightBullet> bulletRef;
    ChargeGraphicsComponent* chargeGraphicsRef;
    float castReleaseTime = 0.0f;
    Unit::Vec2D dir;

    float getRadius() const;
};

#endif // DEPTH_DEFENSIVE_HANDLER_HPP