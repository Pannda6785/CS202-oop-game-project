#ifndef WYRM_DEFENSIVE_HANDLER_HPP
#define WYRM_DEFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class WyrmGraphicsComponent;

class WyrmDefensiveHandler : public TapHandler {
    static constexpr float INVINCIBILITY_DURATION = 1.260f; // major

    // move control
    static constexpr float COOLDOWN = 7.5f;
    static constexpr float MOVEMENT_LOCK = 1.0f;
    static constexpr float ARROW_LOCK = 1.150f;
    static constexpr float ACTION_LOCK = 1.150f;
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.3f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 1.450f;
    
    // bullet
    static constexpr float STARTUP = 0.780f;
    static constexpr float RADIUS = 462;
    static constexpr float LIFETIME = STARTUP + 0.4f;
    static constexpr float BLOOM_TIME = 0.1f;

public:
    WyrmDefensiveHandler(WyrmGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    WyrmGraphicsComponent* graphics;
    
};

#endif // WYRM_DEFENSIVE_HANDLER_HPP
