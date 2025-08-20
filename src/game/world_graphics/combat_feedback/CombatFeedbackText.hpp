#ifndef COMBAT_FEEDBACK_TEXT_HPP
#define COMBAT_FEEDBACK_TEXT_HPP

#include "CombatFeedback.hpp"
#include "../../../UI/game_state/decorative_components/GameText.hpp"

class CombatFeedbackText : public CombatFeedback {
public:
    CombatFeedbackText();
    CombatFeedbackText(Vector2 hitPos, Vector2 hitterPos, std::string text);
    ~CombatFeedbackText() override;
    
    // Text-specific methods
    void setText(const std::string& text);
    void setFontSize(int size);
    void setColor(Color color);
    void loadFont(const std::string& fontPath);
    
    // Override base class methods
    void render() const override;
    void activate() override;
    
protected:
    void updatePosition() override;
    
private:
    GameText gameText;
    Vector2 offset = {20.0f, 20.0f};
};

#endif // COMBAT_FEEDBACK_TEXT_HPP