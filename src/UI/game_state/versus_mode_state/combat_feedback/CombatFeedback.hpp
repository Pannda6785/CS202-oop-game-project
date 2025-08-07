#ifndef COMBAT_FEEDBACK_HPP
#define COMBAT_FEEDBACK_HPP

#include <raylib.h>
#include <string>

enum class HorizontalAlignment {
    LEFT,
    RIGHT
};

enum class VerticalAlignment {
    UP,
    DOWN
};

class CombatFeedback {
public:
    CombatFeedback();
    CombatFeedback(Vector2 hitPos, Vector2 hitterPos);
    virtual ~CombatFeedback() = default;
    
    // Common interface methods
    virtual void update(float dt);
    virtual void render() const = 0; // Pure virtual - must be implemented by subclasses
    
    bool isActive() const;
    float getRemainingTime() const;
    
    // Positioning methods
    void setPosition(Vector2 pos);
    void setHorizontalAlignment(HorizontalAlignment align);
    void setVerticalAlignment(VerticalAlignment align);
    
    // Duration control
    void setDuration(float duration);
    virtual void activate();
    void deactivate();

protected:
    // Common properties
    float timer = 0.0f;     // Remaining display time
    float duration = 0.0f;  // Total display duration
    bool active = false;    // Whether this feedback is currently active
    
    // Positioning properties
    HorizontalAlignment hAlign = HorizontalAlignment::RIGHT;
    VerticalAlignment vAlign = VerticalAlignment::UP;
    Vector2 position = {0.0f, 0.0f};
    Vector2 offset = {10.0f, 10.0f};
    
    // Method for subclasses to implement position updates
    virtual void updatePosition() = 0; // Pure virtual
};

#endif // COMBAT_FEEDBACK_HPP