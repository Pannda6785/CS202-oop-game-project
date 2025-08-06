#ifndef LICH_GRAPHICS_COMPONENT_HPP
#define LICH_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

class LichGraphicsComponent : public CharacterGraphicsComponent {
public:
    LichGraphicsComponent();
    ~LichGraphicsComponent() override;

    void useBasic();
    void useWide();
    void useOffensive();
    void startCastingDefensive();
    void endCastingDefensive(float startup);

protected:
    void loadTextures() override;
    void unloadTextures() override {};
    bool characterSpecificUpdate(float dt) override;

private:
    float remainingCommandCharge = 0.0f;
    float remainingCommandLoop = 0.0f;
    float remainingWhisperCharge = 0.0f;
    float remainingWhisperLoop = 0.0f;
    float remainingOffensiveCharge = 0.0f;
    float remainingOffensiveLoop = 0.0f;
};


#endif // LICH_GRAPHICS_COMPONENT_HPP
