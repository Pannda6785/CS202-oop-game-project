#ifndef BULLET_GRAPHICS_COMPONENT_HPP
#define BULLET_GRAPHICS_COMPONENT_HPP

#include "../../graphics/GraphicsComponent.hpp"
#include "../../Unit.hpp"

class Bullet;

class BulletGraphicsComponent : public GraphicsComponent {
public:
    BulletGraphicsComponent();
    virtual ~BulletGraphicsComponent() = default;

    void registerBullet(const Bullet* bullet);
    
    virtual void render() const;
    virtual void update(float dt) {}
    virtual void makeDone() {}

protected:
    void drawHitboxes() const;

protected:
    const Bullet* bullet = nullptr;

};

#endif // BULLET_GRAPHICS_COMPONENT_HPP
