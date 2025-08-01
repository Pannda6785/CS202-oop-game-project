#ifndef AURA_GRAPHICS_COMPONENT_HPP
#define AURA_GRAPHICS_COMPONENT_HPP

#include "../BulletGraphicsComponent.hpp"
#include <array>
#include <string>

class AuraGraphicsComponent : public BulletGraphicsComponent {
    std::string TEXTURE_PATH = "../assets/sprites/universal/spr_fade_0.png";
    static constexpr float VISIBLE_RATIO = 2.5f / 6.0f;
    static constexpr float TEXTURE_WIDTH = 128.0f;

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