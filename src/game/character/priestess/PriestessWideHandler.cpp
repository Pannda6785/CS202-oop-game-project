#include "PriestessWideHandler.hpp"
#include "../../player/Player.hpp"
#include "PriestessGraphicsComponent.hpp"

PriestessWideHandler::PriestessWideHandler(PriestessGraphicsComponent* graphics)
    : CastHandler(Unit::Move::Wide, 0.06f), graphics(graphics) {}

void PriestessWideHandler::onCastStart() {
    graphics->startCasting();
    // Optional: animation or prep visuals
}

void PriestessWideHandler::onCastRelease() {
    graphics->stopCasting();
    graphics->yell();
    // Optional: trigger spin animation
}
