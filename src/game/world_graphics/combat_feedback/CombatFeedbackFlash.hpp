#ifndef COMBAT_FEEDBACK_FLASH_HPP
#define COMBAT_FEEDBACK_FLASH_HPP

#include "../../../graphics/GraphicsComponent.hpp"

class CombatFeedbackFlash : public GraphicsComponent {
public:
    CombatFeedbackFlash(float duration);
    ~CombatFeedbackFlash() override = default;

    void update(float dt);
    void render() const override;

    bool isAlive() const;

private:
    float duration;
    float timer;
};

#endif // COMBAT_FEEDBACK_FLASH_HPP
