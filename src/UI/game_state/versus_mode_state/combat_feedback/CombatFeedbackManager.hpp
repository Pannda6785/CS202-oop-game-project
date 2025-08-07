#ifndef COMBAT_FEEDBACK_MANAGER_HPP
#define COMBAT_FEEDBACK_MANAGER_HPP

#include "CombatFeedbackText.hpp"
#include "CombatFeedbackEffect.hpp"
#include <vector>
#include <memory>
#include <string>

class CombatFeedbackManager {
public:
    CombatFeedbackManager();
    ~CombatFeedbackManager();

   
    void addHitText(Vector2 hitPos, Vector2 hitterPos, float duration);
    void addHitEffect(Vector2 hitPos, Vector2 hitterPos);
   
    void update(float dt);
    
    void clear();
    
    size_t getActiveCount() const;

private:
    std::vector<std::unique_ptr<CombatFeedback>> feedbacks;
    
    // Helper to create and configure new feedback instances
    float hitTextSize = 100.0f;
    float hitTextDuration = 0.5f;
    Color hitTextColor = WHITE;
};

#endif // COMBAT_FEEDBACK_MANAGER_HPP