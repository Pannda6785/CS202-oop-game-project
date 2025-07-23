#ifndef ARCANIST_GRAPHICS_COMPONENT_HPP
#define ARCANIST_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

class ArcanistGraphicsComponent : public CharacterGraphicsComponent {
public:
    ArcanistGraphicsComponent();
    ~ArcanistGraphicsComponent() override;

protected:
    void loadTextures() override;
    void unloadTextures() override {};

private:

};

#endif // ARCANIST_GRAPHICS_COMPONENT_HPP
