#ifndef LICH_OFFENSIVE_HANDLER_HPP
#define LICH_OFFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

#include <deque>
#include <memory>

class LichGraphicsComponent;
class ButterflyThrall;

class LichOffensiveHandler : public TapHandler {
    static constexpr int MAX_COUNT = 4;
    static constexpr float COOLDOWN = 4.000f;
    static constexpr float MOVEMENT_MODIFIER_VALUE = 0.80f; // force
    static constexpr float MOVEMENT_MODIFIER_DURATION = 3.0f; 

public:
    LichOffensiveHandler(LichGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    LichGraphicsComponent* graphics;

    std::deque<std::weak_ptr<ButterflyThrall>> thralls;
};

#endif // LICH_OFFENSIVE_HANDLER_HPP