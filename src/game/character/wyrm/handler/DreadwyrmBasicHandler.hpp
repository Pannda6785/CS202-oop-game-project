#ifndef DREADWYRM_BASIC_HANDLER_HPP
#define DREADWYRM_BASIC_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class WyrmGraphicsComponent;

class DreadwyrmBasicHandler : public TapHandler {
    static constexpr float MOVEMENT_LOCK = 0.200f;
    static constexpr float MOVEMENT_MODIFIER_AMOUNT = 0.4f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.350f;
    static constexpr float ARROW_MODIFIER_AMOUNT = 0.4f;
    static constexpr float ARROW_MODIFIER_DURATION = 0.350f;
    static constexpr float BASIC_LOCK = 0.650f;
    static constexpr float WIDE_LOCK = 0.500f;

public:
    DreadwyrmBasicHandler(WyrmGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    WyrmGraphicsComponent* graphics;

};

#endif // DREADWYRM_BASIC_HANDLER_HPP