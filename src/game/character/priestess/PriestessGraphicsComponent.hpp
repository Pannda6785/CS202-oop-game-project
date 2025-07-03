#ifndef PRIESTESS_GRAPHICS_COMPONENT_HPP
#define PRIESTESS_GRAPHICS_COMPONENT_HPP

#include "CharacterGraphicsComponent.hpp"

class PriestessGraphicsComponent : public CharacterGraphicsComponent {
public:
    PriestessGraphicsComponent();
    ~PriestessGraphicsComponent() override;

    void useBasic(float loopTime = 0.8f);
    void startCasting();
    void stopCasting();
    void spin();
    void yell(float yellTime = 0.5f);

protected:
    void loadTextures() override;
    void unloadTextures() override;
    bool characterSpecificUpdate(float dt) override;

private:
    bool isCasting = false;
    float remainingYellTime = 0.0f;
    float remainingBasicLoopTime = 0.0f;

};

#endif // PRIESTESS_GRAPHICS_COMPONENT_HPP
