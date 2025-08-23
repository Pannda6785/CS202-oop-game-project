#ifndef COMBAT_FEEDBACK_MANAGER_HPP
#define COMBAT_FEEDBACK_MANAGER_HPP

#include "CombatFeedbackText.hpp"
#include "CombatFeedbackEffect.hpp"
#include "CombatFeedbackFlash.hpp"
#include <vector>
#include <memory>
#include <string>
#include "../../../Unit.hpp"

class CombatFeedbackManager {
public:
    CombatFeedbackManager();
    ~CombatFeedbackManager();

    void update(float dt);    
    void clear();
    void applyHit(Unit::Vec2D hitPos, Unit::Vec2D hitterPos, int health);

    size_t getActiveCount() const;
    
private:
    std::vector<std::unique_ptr<CombatFeedback>> feedbacks;
    std::vector<std::unique_ptr<CombatFeedbackFlash>> flashes;  // << added

    // Helper to create and configure new feedback instances
    float hitTextSize = 100.0f;
    float hitTextDuration = 0.5f;
    Color hitTextColor = WHITE;
    
    void addHitText(Vector2 hitPos, Vector2 hitterPos, float duration);
    void addHitEffect(Vector2 hitPos, Vector2 hitterPos);
    void applyHit(Vector2 hitPos, Vector2 hitterPos, float duration);

    void addLastText(Vector2 hitPos, Vector2 hitterPos, float duration);
    void applyLast(Vector2 hitPos, Vector2 hitterPos, float duration);

    void addBreakText(Vector2 hitPos, Vector2 hitterPos, float duration);
    void applyBreak(Vector2 hitPos, Vector2 hitterPos, float duration);

    void addFlash(float duration);   // << helper
};

#endif // COMBAT_FEEDBACK_MANAGER_HPP
