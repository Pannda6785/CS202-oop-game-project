#ifndef WYRM_DEFENSIVE_HANDLER_HPP
#define WYRM_DEFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class WyrmGraphicsComponent;

class WyrmDefensiveHandler : public TapHandler {
    static constexpr float INVINCIBILITY_DURATION = 1.240f; // major

    // move control
    static constexpr float COOLDOWN = 7.5f;
    static constexpr float MOVEMENT_LOCK = 0.980f;
    static constexpr float ARROW_LOCK = 1.120f;
    static constexpr float ACTION_LOCK = 1.120f;
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.3f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 1.420f;
    
    // bullet
    static constexpr float STARTUP = 0.780f;
    static constexpr float RADIUS = 462;
    static constexpr float LIFETIME = STARTUP + 0.4f;

public:
    WyrmDefensiveHandler(WyrmGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    WyrmGraphicsComponent* graphics;
  
    void spawnBullet();
};

#endif // WYRM_DEFENSIVE_HANDLER_HPP
