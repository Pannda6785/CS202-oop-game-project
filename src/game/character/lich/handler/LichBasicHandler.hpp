#ifndef LICH_BASIC_HANDLER_HPP
#define LICH_BASIC_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class LichGraphicsComponent;

class LichBasicHandler : public TapHandler {
    static constexpr float STARTUP = 0.180f;
    static constexpr float RADIUS = 21;
    static constexpr float SPEED = 30 * 60;
    static constexpr float ANGLE = 6;
    static constexpr float MOVE_LOCK = 0.200f;
    static constexpr float ATTACK_LOCK = 0.500f;

public:
    LichBasicHandler(LichGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    LichGraphicsComponent* graphics;

    void spawnBullets();
};

#endif // LICH_BASIC_HANDLER_HPP