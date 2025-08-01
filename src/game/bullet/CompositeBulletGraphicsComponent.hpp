#ifndef COMPOSITE_BULLET_GRAPHICS_COMPONENT_HPP
#define COMPOSITE_BULLET_GRAPHICS_COMPONENT_HPP

#include "BulletGraphicsComponent.hpp"
#include <vector>
#include <memory>

class CompositeBulletGraphicsComponent : public BulletGraphicsComponent {
public:
    void addComponent(std::unique_ptr<BulletGraphicsComponent> component, float start = 0.0f, float end = 1e9);

    void update(float dt) override;
    void render() const override;

private:
    struct TimedComponent {
        std::unique_ptr<BulletGraphicsComponent> component;
        float start;
        float end;
    };
    std::vector<TimedComponent> components;
    float time = 0.0f;
};

#endif // COMPOSITE_BULLET_GRAPHICS_COMPONENT_HPP