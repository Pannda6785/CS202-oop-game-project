#ifndef PRIESTESS_BASIC_HANDLER_HPP
#define PRIESTESS_BASIC_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class PriestessGraphicsComponent;

class PriestessBasicHandler : public TapHandler {
    static constexpr float COMBO_HOLD = 2.0f;
    static constexpr float SHORT_COOLDOWN = 0.5f;
    static constexpr float LONG_COOLDOWN = 1.3f;

    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.6f;
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.7f;

    static constexpr float SHORT_ARROW_MODIFIER_DURATION = 0.5f;
    static constexpr float LONG_ARROW_MODIFIER_DURATION = 1.2f;
    static constexpr float ARROW_MODIFIER_AMOUNT = 0.3f;

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
    
};

#endif // PRIESTESS_BASIC_HANDLER_HPP
