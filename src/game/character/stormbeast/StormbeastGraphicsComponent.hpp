#ifndef STORMBEAST_GRAPHICS_COMPONENT_HPP
#define STORMBEAST_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

class StormbeastGraphicsComponent : public CharacterGraphicsComponent {
public:
    StormbeastGraphicsComponent();
    ~StormbeastGraphicsComponent() override;

protected:
    void loadTextures() override;
    void unloadTextures() override {};

private:

};

#endif // STORMBEAST_GRAPHICS_COMPONENT_HPP
