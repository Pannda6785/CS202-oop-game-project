#ifndef DEPTH_GRAPHICS_COMPONENT_HPP
#define DEPTH_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

class DepthGraphicsComponent : public CharacterGraphicsComponent {
public:
    DepthGraphicsComponent();
    ~DepthGraphicsComponent() override;

    void useBasic(float loopTime = 0.6f);
    void useWide(float loopTime = 1.0f);
    void useOffensive();
    void startCastingDefensive();
    void endCastingDefensive(float loopTime = 0.9f);

protected:
    void loadTextures() override;
    void unloadTextures() override {};
    bool characterSpecificUpdate(float dt) override;

private:
    float remainingLoopTime = 0.0f;
    bool isBasic = false;
    bool isWide = false;
    bool isDefensive = false;
};

#endif // DEPTH_GRAPHICS_COMPONENT_HPP
