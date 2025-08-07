#ifndef DREADWYRM_DEFENSIVE_HANDLER_HPP
#define DREADWYRM_DEFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class WyrmGraphicsComponent;

class DreadwyrmDefensiveHandler : public TapHandler {
    static constexpr float INVINCIBILITY_DURATION = 0.950f; // major

    // move control
    static constexpr float COOLDOWN = 7.5f;
    static constexpr float MOVEMENT_LOCK = 1.000f;
    static constexpr float ARROW_LOCK = 1.120f;
    static constexpr float ACTION_LOCK = 1.120f;
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.8f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 1.320f;
    
    // bullet
    static constexpr float STARTUP = 0.850f;
    static constexpr float RADIUS = 462;
    static constexpr float LIFETIME = STARTUP + 0.4f;

public:
    DreadwyrmDefensiveHandler(WyrmGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    WyrmGraphicsComponent* graphics;
  
    void spawnBullet();
};

#endif // DREADWYRM_DEFENSIVE_HANDLER_HPP