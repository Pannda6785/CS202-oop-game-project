#ifndef HERO_OFFENSIVE_HANDLER_HPP
#define HERO_OFFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class HeroGraphicsComponent;

class HeroOffensiveHandler : public TapHandler {
    static constexpr float INVINCIBILITY_DURATION = 0.350f; // minor
    static constexpr float MOVEMENT_MODIFIER_VALUE_1 = 2.0f;
    static constexpr float MOVEMENT_MODIFIER_DURATION_1 = 0.2f;
    static constexpr float MOVEMENT_MODIFIER_VALUE_2 = 0.4f;
    static constexpr float MOVEMENT_MODIFIER_DURATION_2 = 0.4f;

    static constexpr float COOLDOWN = 4.0f;
    static constexpr float ARROW_LOCK = 0.350f;
    static constexpr float ACTION_LOCK = 0.400f;

public:
    HeroOffensiveHandler(HeroGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;

protected:
    void tap(bool isFocusing) override;

private:
    HeroGraphicsComponent* graphics;

    float timer;

};

#endif // HERO_OFFENSIVE_HANDLER_HPP