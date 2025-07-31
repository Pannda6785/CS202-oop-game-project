#ifndef HERO_BASIC_HANDLER_HPP
#define HERO_BASIC_HANDLER_HPP

#include "../../handlerCharacter/HoldHandler.hpp"

class HeroGraphicsComponent;

class HeroBasicHandler : public HoldHandler {
    // bullet 
    static constexpr float STARTUP = 0.180f;
    static constexpr float RADIUS = 10;
    static constexpr float SPEED = 720;
    static constexpr float SPEED_1 = 870;
    static constexpr float SPEED_2 = 900;
    static constexpr float SPEED_3 = 1020;

    // move control
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.4f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.400f;
    static constexpr float ARROW_MODIFIER_AMOUNT = 0.4f;
    static constexpr float ARROW_MODIFIER_DURATION = 0.350f;
    static constexpr float ACTION_LOCK = 0.350f;
    static constexpr float COMBO_HOLD = 0.500f;

public:
    HeroBasicHandler(HeroGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;
    void listen(Unit::Move move) override;

protected:
    void tick(bool isFocusing) override;

private:
    HeroGraphicsComponent* graphics;
    int step = 0;
    float comboHold = 0.0f;
    bool lastFocusing = false;

    void spawnBullet(bool isFocusing);
};

#endif // HERO_BASIC_HANDLER_HPP