#ifndef BULLET_GRAPHICS_COMPONENT_HPP
#define BULLET_GRAPHICS_COMPONENT_HPP

#include "../../graphics/GraphicsComponent.hpp"
#include "../../Unit.hpp"

class Bullet;

class BulletGraphicsComponent : public GraphicsComponent {
public:
    BulletGraphicsComponent(const Bullet* bullet);
    virtual ~BulletGraphicsComponent() = default;
    
    virtual void render() const;
    virtual void update(float dt) {}

protected:
    void drawHitboxes() const;

protected:
    const Bullet* bullet = nullptr;

};

#endif // BULLET_GRAPHICS_COMPONENT_HPP
