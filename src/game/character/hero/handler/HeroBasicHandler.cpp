#include "HeroBasicHandler.hpp"
#include "../../../player/Player.hpp"
#include "../HeroGraphicsComponent.hpp"

HeroBasicHandler::HeroBasicHandler(HeroGraphicsComponent* graphics)
    : HoldHandler(Unit::Move::Basic), graphics(graphics) {}

void HeroBasicHandler::update(float dt, const InputBufferer* input) {
    // You may want to update graphics or handle charge visuals here
    if (graphics) graphics->update(dt);
}

void HeroBasicHandler::listen(Unit::Move move) {
    // Reset state or combo if needed when move changes
}

void HeroBasicHandler::onHoldStart() {
    // To be implemented by user
}

void HeroBasicHandler::onHoldRelease(bool isInterupted) {
    // To be implemented by user
}

void HeroBasicHandler::spawnBullet() {
    // To be
}