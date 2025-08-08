#ifndef ARCANIST_GRAPHICS_COMPONENT_HPP
#define ARCANIST_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

class ArcanistGraphicsComponent : public CharacterGraphicsComponent {
public:
    ArcanistGraphicsComponent();
    ~ArcanistGraphicsComponent() override;

    void useOffensive();

protected:
    void loadTextures() override;
    void unloadTextures() override {};
    bool characterSpecificUpdate(float dt) override;

private:
    float remainingSmugCharge = 0.0f;
    float remainingSmugLoop = 0.0f;

};

#endif // ARCANIST_GRAPHICS_COMPONENT_HPP
