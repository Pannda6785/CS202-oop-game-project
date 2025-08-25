#ifndef COMBAT_FEEDBACK_EFFECT_HPP
#define COMBAT_FEEDBACK_EFFECT_HPP

#include "CombatFeedback.hpp"
#include "../../../UI/game_state/decorative_components/artwork/Artwork.hpp"

class CombatFeedbackEffect : public CombatFeedback {
public:
    CombatFeedbackEffect();
    CombatFeedbackEffect(Vector2 hitPos, Vector2 hitterPos);
    ~CombatFeedbackEffect() override;
    
    // Effect-specific methods
    bool addTexture(const std::string& filePath);
    void setScale(float scale);
    void setAnimationPeriod(float period);
    void setFlip(bool flip);
    
    // Override base class methods
    void update(float dt) override;
    void render() const override;
    void activate() override;
    
protected:
    void updatePosition() override;
    
private:
    Artwork artwork;
    Vector2 hitEffectOriginRatio = {0.75f, 0.83f};
};

#endif // COMBAT_FEEDBACK_EFFECT_HPP