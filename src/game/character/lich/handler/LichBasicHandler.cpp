#include "LichBasicHandler.hpp"
#include "../../../player/Player.hpp"
#include "../LichGraphicsComponent.hpp"

LichBasicHandler::LichBasicHandler(LichGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Basic), graphics(graphics) {}

void LichBasicHandler::tap(bool isFocusing) {
    // graphics->useBasic();
    // TODO: spawn basic bullet(s) here
    player->applyImplicitMoveLock();
    player->applyLock(Unit::Lock::BasicLock, 0.5f);
}