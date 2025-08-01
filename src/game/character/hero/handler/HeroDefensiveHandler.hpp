#ifndef HERO_DEFENSIVE_HANDLER_HPP
#define HERO_DEFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class HeroGraphicsComponent;

class HeroDefensiveHandler : public TapHandler {
    static constexpr float INVINCIBILITY_DURATION = 0.500f; // minor
    static constexpr float STUN_DURATION = 1.2f;

    // move control
    static constexpr float COOLDOWN = 8.5f;
    static constexpr float MOVEMENT_LOCK = 0.6f;
    static constexpr float ATTACK_LOCK = 0.600f;
    static constexpr float SPELL_LOCK = 0.725f;

    // bullet
    static constexpr float STARTUP = 0.425f;
    static constexpr float RADIUS = 335;
    static constexpr float LIFETIME = 0.5f; // for graphics to live
    static constexpr float BLOOM_TIME = 0.1f;

public:
    HeroDefensiveHandler(HeroGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    HeroGraphicsComponent* graphics;
};

#endif // HERO_DEFENSIVE_HANDLER_HPP