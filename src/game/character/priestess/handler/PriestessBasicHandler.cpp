#include "PriestessBasicHandler.hpp"

#include "../../../player/Player.hpp"
#include "../PriestessGraphicsComponent.hpp"
#include "../bullet/Sunburst.hpp"

PriestessBasicHandler::PriestessBasicHandler(PriestessGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Basic), graphics(graphics) {}

void PriestessBasicHandler::update(float deltaTime, const InputBufferer* input) {
    comboHold = std::max(0.0f, comboHold - deltaTime);
    if (comboHold < Unit::EPS) {
        step = 0;
    }
}

void PriestessBasicHandler::listen(Unit::Move move) {
    if (move != Unit::Move::Basic) {
        comboHold = 0;
        step = 0;
    }
}

void PriestessBasicHandler::tap(bool isFocusing) {
    graphics->useBasic();
    player->spawnBullet(std::make_unique<Sunburst>(player->getPlayerId(), player->getPosition(), 
                        player->getArrow(), player->getTargetPosition(), isFocusing));

    step++;
    player->applyImplicitMoveLock();
    player->applyLock(Unit::moveToLock(move), step < 3 ? SHORT_LOCK : LONG_LOCK);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_AMOUNT);
    player->applyModifier(Unit::Modifier::ArrowModifier, step < 3 ? SHORT_ARROW_MODIFIER_DURATION : LONG_ARROW_MODIFIER_DURATION, ARROW_MODIFIER_AMOUNT);
    if (step < 3) {
        comboHold = COMBO_HOLD;
    } else {
        step = 0;
        comboHold = 0;
    }
}
