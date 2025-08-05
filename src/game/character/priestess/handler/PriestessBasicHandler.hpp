#ifndef PRIESTESS_BASIC_HANDLER_HPP
#define PRIESTESS_BASIC_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class PriestessGraphicsComponent;

class PriestessBasicHandler : public TapHandler {
    static constexpr float RADIUS = 240.0f;   
    static constexpr float ACTIVE_TIME = 0.9f; // how long after start up that it linger in place
    static constexpr float BASE_STARTUP = 0.780f;
    static constexpr float FOCUS_STARTUP = 0.858f; // use this instead when focused
    static constexpr float DISTANCE_SCALAR = 0.00055f; // per distance startup
    static constexpr float SPEED = 1 / DISTANCE_SCALAR; // 1818 units per second for 0.55
    static constexpr float FOCUS_DISTANCE_SHORTENING = 200.0f; // 200px closer

    static constexpr float SHORT_ARROW_MODIFIER_DURATION = 0.5f;
    static constexpr float LONG_ARROW_MODIFIER_DURATION = 1.2f;
    static constexpr float ARROW_MODIFIER_AMOUNT = 0.3f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.6f;
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.7f;

    static constexpr float COMBO_HOLD = 2.0f;
    static constexpr float SHORT_LOCK = 0.5f;
    static constexpr float LONG_LOCK = 1.3f;

public:
    PriestessBasicHandler(PriestessGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;
    void listen(Unit::Move move) override;

protected:
    void tap(bool isFocusing) override;

private:
    PriestessGraphicsComponent* graphics;
    int step = 0;
    float comboHold = 0.0f;
    
    void spawnBullet(bool isFocusing);
};

#endif // PRIESTESS_BASIC_HANDLER_HPP
