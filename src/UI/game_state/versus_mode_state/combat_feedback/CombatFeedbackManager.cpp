#include "CombatFeedbackManager.hpp"
#include <algorithm>

CombatFeedbackManager::CombatFeedbackManager() = default;

CombatFeedbackManager::~CombatFeedbackManager() {
    clear();
}

void CombatFeedbackManager::addHitText(Vector2 hitPos, Vector2 hitterPos, float duration) {
    auto feedback = std::make_unique<CombatFeedbackText>(hitPos, hitterPos);
    feedback->setDuration(duration);
    feedback->activate();
    feedbacks.push_back(std::move(feedback));
}

void CombatFeedbackManager::addHitEffect(Vector2 hitPos, Vector2 hitterPos) {
    auto feedback = std::make_unique<CombatFeedbackEffect>(hitPos, hitterPos);
    feedback->activate();
    feedbacks.push_back(std::move(feedback));
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