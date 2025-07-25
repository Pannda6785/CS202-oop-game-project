#ifndef BULLET_GRAPHICS_COMPONENT_HPP
#define BULLET_GRAPHICS_COMPONENT_HPP

#include "../../graphics/GraphicsComponent.hpp"
#include "../../Unit.hpp"

class Bullet;

class BulletGraphicsComponent : public GraphicsComponent {
public:
    BulletGraphicsComponent(bool drawHitbox = false);
    virtual ~BulletGraphicsComponent() = default;
    virtual void registerOwner(const Bullet* owner);

    virtual void render() const = 0;
    virtual void update(float dt) {}

protected:
    void drawHitboxes() const;

private:
    const Bullet* owner = nullptr;
    bool drawHitbox;

};

#endif // BULLET_GRAPHICS_COMPONENT_HPP
