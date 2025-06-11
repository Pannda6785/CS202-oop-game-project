#ifndef BULLET_GRAPHICS_COMPONENT_HPP
#define BULLET_GRAPHICS_COMPONENT_HPP

#include "../../Unit.hpp"
#include "../../graphics/GraphicsComponent.hpp" 

// TO DO

class BulletGraphicsComponent : public GraphicsComponent {
public:
    void render(Renderer& renderer) const override;

private:

};

#endif // BULLET_GRAPHICS_COMPONENT_HPP
