#ifndef ARCANIST_DEFENSIVE_HANDLER_HPP
#define ARCANIST_DEFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class ArcanistGraphicsComponent;

class ArcanistDefensiveHandler : public TapHandler {
    static constexpr float RADIUS = 240.0f;   
    static constexpr float CLEANSE_RADIUS = RADIUS * 0.92f;   
    static constexpr float ACTIVE_TIME = 3.000f;
    static constexpr float MIN_STARTUP = 0.475f;
    static constexpr float MAX_SPEED = 3600.0f;
    static constexpr float START_GAINING_WHEN = 0.1f;
    static constexpr float STOP_GAINING_WHEN = 2.550f;

    static constexpr float INVINCIBILITY = 0.500f;
    static constexpr float INVINCIBILITY_REFRESH = 0.150f;
    static constexpr float INVINCIBILITY_DOWN = 0.500f;
    static constexpr float BARRIER_MOVEMENT_MODIFIER_VALUE = 0.7f;
    static constexpr float BARRIER_MOVEMENT_MODIFIER_DURATION = 0.150f;
    static constexpr float TIME_STOP_DURATION = 3.0f;

    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.350f;
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.25f;
    static constexpr float SPELL_LOCK = 0.200f;
    static constexpr float COOLDOWN = 13.0f;

public:
    ArcanistDefensiveHandler(ArcanistGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    ArcanistGraphicsComponent* graphics;
    
    void spawnBullet(bool isFocusing);
    float computeTravelTime(float toTravel);
};

#endif // ARCANIST_DEFENSIVE_HANDLER_HPP
