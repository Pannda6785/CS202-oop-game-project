#include "CombatFeedbackManager.hpp"
#include "../../../audio/AudioManager.hpp"
#include <algorithm>
#include <iostream>

CombatFeedbackManager::CombatFeedbackManager() = default;

CombatFeedbackManager::~CombatFeedbackManager() {
    clear();
}

void CombatFeedbackManager::applyHit(Unit::Vec2D hitPos, Unit::Vec2D hitterPos, int health) {
    addFlash(0.30f); // quick white flash
    float hitDuration = 0.8f;
    switch(health) {
        case(1):
            applyLast({hitPos.x, hitPos.y}, {hitterPos.x, hitterPos.y}, hitDuration);
            break;
        case(0):
            applyBreak({hitPos.x, hitPos.y}, {hitterPos.x, hitterPos.y}, hitDuration);
            break;
        default:
            applyHit({hitPos.x, hitPos.y}, {hitterPos.x, hitterPos.y}, hitDuration);
    }
}

void CombatFeedbackManager::addHitText(Vector2 hitPos, Vector2 hitterPos, float duration) {
    auto feedback = std::make_unique<CombatFeedbackText>(hitPos, hitterPos, "HIT!!");
    feedback->setDuration(duration);
    feedback->activate();
    feedbacks.push_back(std::move(feedback));
    AudioManager::getInstance().playSound("HitPlayer");
}

void CombatFeedbackManager::addHitEffect(Vector2 hitPos, Vector2 hitterPos) {
    auto feedback = std::make_unique<CombatFeedbackEffect>(hitPos, hitterPos);
    feedback->activate();
    feedbacks.push_back(std::move(feedback));
}

void CombatFeedbackManager::applyHit(Vector2 hitPos, Vector2 hitterPos, float duration) {
    addHitText(hitPos, hitterPos, duration);
    addHitEffect(hitPos, hitterPos);
}

void CombatFeedbackManager::addLastText(Vector2 hitPos, Vector2 hitterPos, float duration) {
    auto feedback = std::make_unique<CombatFeedbackText>(hitPos, hitterPos, "LAST!!");
    feedback->setDuration(duration);
    feedback->activate();
    feedbacks.push_back(std::move(feedback));
    AudioManager::getInstance().playSound("HitPlayer");
}

void CombatFeedbackManager::applyLast(Vector2 hitPos, Vector2 hitterPos, float duration) {
    addLastText(hitPos, hitterPos, duration);
    addHitEffect(hitPos, hitterPos);
    addFlash(0.25f); // slightly longer flash
}

void CombatFeedbackManager::addBreakText(Vector2 hitPos, Vector2 hitterPos, float duration) {
    auto feedback = std::make_unique<CombatFeedbackText>(hitPos, hitterPos, "BREAK!!");
    feedback->setDuration(duration);
    feedback->activate();
    feedbacks.push_back(std::move(feedback));
    AudioManager::getInstance().playSound("HealthBreak");
    std::cout << "Play sound health break" << std::endl;
}

void CombatFeedbackManager::applyBreak(Vector2 hitPos, Vector2 hitterPos, float duration) {
    addBreakText(hitPos, hitterPos, duration);
    addHitEffect(hitPos, hitterPos);
    addFlash(0.4f); // longest flash for break
}

void CombatFeedbackManager::addFlash(float duration) {
    auto flash = std::make_unique<CombatFeedbackFlash>(duration);
    flashes.push_back(std::move(flash));
}

void CombatFeedbackManager::update(float dt) {
    // Update normal feedback
    for (auto& feedback : feedbacks) {
        feedback->update(dt);
    }

    feedbacks.erase(
        std::remove_if(feedbacks.begin(), feedbacks.end(),
            [](const std::unique_ptr<CombatFeedback>& f) { return !f->isActive(); }),
        feedbacks.end()
    );

    // Update flashes
    for (auto& flash : flashes) {
        flash->update(dt);
    }

    flashes.erase(
        std::remove_if(flashes.begin(), flashes.end(),
            [](const std::unique_ptr<CombatFeedbackFlash>& f) { return !f->isAlive(); }),
        flashes.end()
    );
}

void CombatFeedbackManager::clear() {
    feedbacks.clear();
    flashes.clear();
}

size_t CombatFeedbackManager::getActiveCount() const {
    return feedbacks.size() + flashes.size();
}
