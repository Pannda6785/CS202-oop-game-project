#ifndef PRIESTESS_DEFENSIVE_HANDLER_HPP
#define PRIESTESS_DEFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class PriestessGraphicsComponent;

class PriestessDefensiveHandler : public TapHandler {
    static constexpr float COOLDOWN = 15.0f;
    static constexpr float MOVEMENT_LOCK = 0.5f;

    static constexpr float BASE_RADIUS = 480.0f;
    static constexpr float CLEANSE_RADIUS = BASE_RADIUS * 0.92f;
    static constexpr float LIFETIME = 1.5f;
    static constexpr float INVINCIBILITY_DURATION = 0.5f; // each tick apply this
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.25f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 1.5f;
    
public:
    PriestessDefensiveHandler(PriestessGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    PriestessGraphicsComponent* graphics;    

    void spawnBullet();
};

#endif // PRIESTESS_DEFENSIVE_HANDLER_HPP
