#ifndef LICH_DEFENSIVE_HANDLER_HPP
#define LICH_DEFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/CastHandler.hpp"
#include <memory>
#include <vector>

class LichGraphicsComponent;
class StraightBullet;
class ChargeGraphicsComponent;

class LichDefensiveHandler : public CastHandler {


    static constexpr float MIN_CASTING_TIME = 0.1f;
    static constexpr float MOVEMENT_MODIFIER_VALUE_CASTING = 0.1f; 
    static constexpr float MOVEMENT_MODIFIER_DURATION_CASTING = 0.1f;

    static constexpr float COOLDOWN = 10;
    static constexpr float MOVEMENT_MODIFIER_VALUE_RELEASE = 1.2f;
    static constexpr float MOVEMENT_MODIFIER_DURATION_RELEASE = 0.430f;

    static constexpr float INVINCIBILITY = 0.8; // minor

    static constexpr float DURATION = 20;
    static constexpr float MIN_RADIUS = 250.0f;
    static constexpr float RADIUS_RATE = 82.5; // radius per second
    static constexpr float STARTUP = 0.610f;
    static constexpr float CLEANSE_RATIO = 0.96f;

public:
    LichDefensiveHandler(LichGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;

protected:
    void onCastStart() override;
    void onCastRelease(bool isInterrupted = false) override;

private:
    LichGraphicsComponent* graphics;

    std::vector<std::pair<float, std::weak_ptr<StraightBullet>>> pastBullets;
    std::weak_ptr<StraightBullet> bulletRef;
    ChargeGraphicsComponent* chargeGraphicsRef = nullptr;

    float getRadius() const;
};

#endif // LICH_DEFENSIVE_HANDLER_HPP