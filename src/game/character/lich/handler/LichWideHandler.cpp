#include "LichWideHandler.hpp"
#include "../../../player/Player.hpp"
#include "../LichGraphicsComponent.hpp"

LichWideHandler::LichWideHandler(LichGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Wide), graphics(graphics) {}

void LichWideHandler::tap(bool isFocusing) {
    // graphics->useWide();
    // TODO: spawn wide bullet(s) here
    player->applyImplicitMoveLock();
    player->applyLock(Unit::Lock::WideLock, 0.5f);
}