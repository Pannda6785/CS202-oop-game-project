#ifndef WYRM_GRAPHICS_COMPONENT_HPP
#define WYRM_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

class WyrmGraphicsComponent : public CharacterGraphicsComponent {
public:
    WyrmGraphicsComponent();
    ~WyrmGraphicsComponent() override;

    void useBasic();
    void useOffensive(bool firstUse, float chargeDuration, float offensiveDuration);
    void roar(float chargeDuration, float roarDuration);

protected:
    void loadTextures() override;
    void unloadTextures() override {};
    bool characterSpecificUpdate(float dt) override;

private:
    float remainingRoarChargeTime = 0.0f;
    float remainingRoarTime = 0.0f;
    float remainingOffensiveChargeTime = 0.0f;
    float remainingOffensiveTime = 0.0f;
};

#endif // WYRM_GRAPHICS_COMPONENT_HPP
