#ifndef BULLET_GRAPHICS_COMPONENT_HPP
#define BULLET_GRAPHICS_COMPONENT_HPP

#include "../../graphics/GraphicsComponent.hpp"
#include "../../Unit.hpp"

class BulletGraphicsComponent : public GraphicsComponent {
public:
    BulletGraphicsComponent() { layer = Unit::Layer::Bullet; }
    virtual ~BulletGraphicsComponent() = default;
    virtual void render() const override = 0;
};

#endif // BULLET_GRAPHICS_COMPONENT_HPP
