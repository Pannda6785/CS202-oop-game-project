#include "PriestessWideHandler.hpp"

#include "../../../player/Player.hpp"
#include "../PriestessGraphicsComponent.hpp"

PriestessWideHandler::PriestessWideHandler(PriestessGraphicsComponent* graphics)
    : CastHandler(Unit::Move::Wide, 0.06f), graphics(graphics) {}

void PriestessWideHandler::update(float dt, const InputBufferer* input) {
    if (isCasting) {
    }
}

void PriestessWideHandler::onCastStart() {
    graphics->startCasting();
    
}

void PriestessWideHandler::onCastRelease() {
    graphics->stopCasting();
    graphics->yell();

}
