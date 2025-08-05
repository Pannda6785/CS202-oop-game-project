#ifndef AURA_GRAPHICS_COMPONENT_HPP
#define AURA_GRAPHICS_COMPONENT_HPP

#include "../BulletGraphicsComponent.hpp"
#include <array>
#include <string>

class AuraGraphicsComponent : public BulletGraphicsComponent {
public:
    AuraGraphicsComponent(std::array<int, 4> color,
                         float startRadius,
                         float endRadius,
                         float duration);

    void update(float dt) override;
    void render() const override;

private:
    float startRadius;
    float endRadius;
    float duration;
    std::array<int, 4> color;
    float time = 0.0f;
};

#endif // AURA_GRAPHICS_COMPONENT_HPP