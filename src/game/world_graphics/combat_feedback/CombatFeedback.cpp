#include "CombatFeedback.hpp"

CombatFeedback::CombatFeedback() = default;

CombatFeedback::CombatFeedback(Vector2 hitPos, Vector2 hitterPos)
    : position(hitPos), hAlign(hitPos.x <= hitterPos.x ? HorizontalAlignment::LEFT : HorizontalAlignment::RIGHT),
      vAlign(hitPos.y <= hitterPos.y ? VerticalAlignment::UP : VerticalAlignment::DOWN) {
    // Default duration for combat feedback
    active = false;
    timer = 0.0f;
}

void CombatFeedback::update(float dt) {
    if (active) {
        timer -= dt;
        if (timer <= 0.0f) {
            active = false;
            timer = 0.0f;
        }
    }
}

bool CombatFeedback::isActive() const {
    return active;
}

float CombatFeedback::getRemainingTime() const {
    return timer;
}

void CombatFeedback::setPosition(Vector2 pos) {
    position = pos;
    if (active) {
        updatePosition();
    }
}

void CombatFeedback::setHorizontalAlignment(HorizontalAlignment align) {
    hAlign = align;
    if (active) {
        updatePosition();
    }
}

void CombatFeedback::setVerticalAlignment(VerticalAlignment align) {
    vAlign = align;
    if (active) {
        updatePosition();
    }
}

void CombatFeedback::setDuration(float dur) {
    duration = dur;
}

void CombatFeedback::activate() {
    timer = duration;
    active = true;
    updatePosition();
}

void CombatFeedback::deactivate() {
    active = false;
    timer = 0.0f;
}