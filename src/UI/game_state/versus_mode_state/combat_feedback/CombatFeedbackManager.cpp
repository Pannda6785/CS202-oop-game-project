#include "CombatFeedbackManager.hpp"
#include "../../../../audio/AudioManager.hpp"
#include <algorithm>
#include <iostream>

CombatFeedbackManager::CombatFeedbackManager() = default;

CombatFeedbackManager::~CombatFeedbackManager() {
    clear();
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
}

void CombatFeedbackManager::update(float dt) {
    // Update all feedback instances
    for (auto& feedback : feedbacks) {
        feedback->update(dt);
    }
    
    // Remove inactive feedback
    feedbacks.erase(
        std::remove_if(
            feedbacks.begin(), 
            feedbacks.end(),
            [](const std::unique_ptr<CombatFeedback>& feedback) { 
                return !feedback->isActive(); 
            }
        ),
        feedbacks.end()
    );
}

void CombatFeedbackManager::clear() {
    feedbacks.clear();
}

size_t CombatFeedbackManager::getActiveCount() const {
    return feedbacks.size();
}