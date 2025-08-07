#ifndef WYRM_GRAPHICS_COMPONENT_HPP
#define WYRM_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

#include <string>

class WyrmGraphicsComponent : public CharacterGraphicsComponent {
public:
    WyrmGraphicsComponent();
    ~WyrmGraphicsComponent() override;

    void transform();
    void detransform();

    void command(float chargeDuration, float loopDuration);
    void blast(float chargeDuration, float loopDuration);
    void roar(float chargeDuration, float loopDuration);

protected:
    void loadTextures() override;
    void unloadTextures() override {};
    bool characterSpecificUpdate(float dt) override;

private:
    float remainingCommandCharge = 0.0f;
    float remainingCommandLoop = 0.0f;
    float remainingRoarCharge = 0.0f;
    float remainingRoarLoop = 0.0f;
    float remainingBlastCharge = 0.0f;
    float remainingBlastLoop = 0.0f;

    void _loadTextures(std::string path);
};

#endif // WYRM_GRAPHICS_COMPONENT_HPP
