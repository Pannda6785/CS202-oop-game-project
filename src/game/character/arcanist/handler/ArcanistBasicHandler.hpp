#ifndef ARCANIST_BASIC_HANDLER_HPP
#define ARCANIST_BASIC_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class ArcanistGraphicsComponent;

class ArcanistBasicHandler : public TapHandler {
    static constexpr float STARTUP = 0.180f;
    static constexpr float RADIUS = 30;
    static constexpr float SPEED1 = 528.0f;
    static constexpr float SPEED2 = 610.5f;
    static constexpr float SPEED3 = 693.0f;

    static constexpr float ARROW_MODIFIER_VALUE = 0.1f;
    static constexpr float ARROW_MODIFIER_DURATION = 0.880f;
    static constexpr float ATTACK_LOCK = 0.880f;

public:
    ArcanistBasicHandler(ArcanistGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    ArcanistGraphicsComponent* graphics;

    void spawnBullet();
    
};

#endif // ARCANIST_BASIC_HANDLER_HPP