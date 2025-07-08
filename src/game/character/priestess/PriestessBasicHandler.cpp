#include "PriestessBasicHandler.hpp"
#include "../../player/Player.hpp"
#include "PriestessGraphicsComponent.hpp"

PriestessBasicHandler::PriestessBasicHandler(PriestessGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Basic), graphics(graphics) {}

void PriestessBasicHandler::tap() {
    graphics->useBasic();
}
