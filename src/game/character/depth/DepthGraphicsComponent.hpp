#ifndef DEPTH_GRAPHICS_COMPONENT_HPP
#define DEPTH_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

class DepthGraphicsComponent : public CharacterGraphicsComponent {
public:
    DepthGraphicsComponent();
    ~DepthGraphicsComponent() override;

protected:
    void loadTextures() override;
    void unloadTextures() override {};

private:

};

#endif // DEPTH_GRAPHICS_COMPONENT_HPP
