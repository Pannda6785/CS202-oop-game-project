#ifndef DEPTH_BASIC_HANDLER_HPP
#define DEPTH_BASIC_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

#include <memory>

class DepthGraphicsComponent;
class Whirlpool;

class DepthBasicHandler : public TapHandler {
    static constexpr float MOVEMENT_MODIFIER_VALUE = 0.3f;
    static constexpr float MOVEMENT_MODIFIER_DURATION = 0.480f;
    static constexpr float ATTACK_LOCK = 1.480f;

public:
    DepthBasicHandler(DepthGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    DepthGraphicsComponent* graphics;
    std::weak_ptr<Whirlpool> whirlpoolRef;
};

#endif // DEPTH_BASIC_HANDLER_HPP