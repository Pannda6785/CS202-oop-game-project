#ifndef WYRM_GRAPHICS_COMPONENT_HPP
#define WYRM_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

class WyrmGraphicsComponent : public CharacterGraphicsComponent {
public:
    WyrmGraphicsComponent();
    ~WyrmGraphicsComponent() override;

    void useBasic();

protected:
    void loadTextures() override;
    void unloadTextures() override {};
    bool characterSpecificUpdate(float dt) override;

private:

};

#endif // WYRM_GRAPHICS_COMPONENT_HPP
