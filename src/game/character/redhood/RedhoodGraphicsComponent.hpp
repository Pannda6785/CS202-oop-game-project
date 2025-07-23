#ifndef REDHOOD_GRAPHICS_COMPONENT_HPP
#define REDHOOD_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

class RedhoodGraphicsComponent : public CharacterGraphicsComponent {
public:
    RedhoodGraphicsComponent();
    ~RedhoodGraphicsComponent() override;

protected:
    void loadTextures() override;
    void unloadTextures() override {};

private:

};

#endif // REDHOOD_GRAPHICS_COMPONENT_HPP
