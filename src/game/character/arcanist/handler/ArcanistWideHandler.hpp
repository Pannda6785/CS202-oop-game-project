#ifndef ARCANIST_WIDE_HANDLER_HPP
#define ARCANIST_WIDE_HANDLER_HPP

#include "../../handlerCharacter/HoldHandler.hpp"

class ArcanistGraphicsComponent;

class ArcanistWideHandler : public HoldHandler {
    // bullet 
    static constexpr float STARTUP = 0.330f;
    static constexpr float DELAY = 0.160f;
    static constexpr float RADIUS = 20;
    static constexpr float SPEED = 660;

    // move control
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.55f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.400f;
    static constexpr float ARROW_MODIFIER_AMOUNT = 0.1f;
    static constexpr float ARROW_MODIFIER_DURATION = 0.400f;
    static constexpr float ATTACK_LOCK = 0.340f;
    static constexpr float COMBO_HOLD = 0.760f;

public:
    ArcanistWideHandler(ArcanistGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;
    void listen(Unit::Move move) override;

protected:
    void tick(bool isFocusing) override;

private:
    ArcanistGraphicsComponent* graphics;
    int step = 0;
    float comboHold = 0.0f;
    bool lastFocusing = false;

    void spawnBullet();
};

#endif // ARCANIST_WIDE_HANDLER_HPP