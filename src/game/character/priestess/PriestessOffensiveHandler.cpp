#include "PriestessOffensiveHandler.hpp"
#include "../../player/Player.hpp"
#include "PriestessGraphicsComponent.hpp"

PriestessOffensiveHandler::PriestessOffensiveHandler(PriestessGraphicsComponent* graphics)
    : CastHandler(Unit::Move::Offensive, 0.06f), graphics(graphics) {}

void PriestessOffensiveHandler::onCastStart() {
    graphics->startCasting();
    // Optional: start casting animation
}

void PriestessOffensiveHandler::onCastRelease() {
    graphics->stopCasting();
    graphics->spin();
    // Optional: trigger release visuals
}
