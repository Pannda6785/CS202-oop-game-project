#ifndef RIPPLE_GRAPHICS_COMPONENT_HPP
#define RIPPLE_GRAPHICS_COMPONENT_HPP

#include "../BulletGraphicsComponent.hpp"
#include <array>
#include <string>

class RippleGraphicsComponent : public BulletGraphicsComponent {
    std::string TEXTURE_PATH = "../assets/sprites/universal/spr_bullet_fade_0_1.png";
    static constexpr float VISIBLE_RATIO = 1.0f;
    static constexpr float TEXTURE_WIDTH = 520.0f;
    
public:
    RippleGraphicsComponent(std::array<int, 4> color, 
                           int numRipples,
                           float startRadius,
                           float endRadius,
                           float duration,
                           float frequency,
                           float thickness);

    void update(float dt) override;
    void render() const override;

private:
    int numRipples;
    float startRadius;
    float endRadius;
    float duration;
    float frequency;
    float thickness;
    std::array<int, 4> color;
    float time = 0.0f;
};

#endif // RIPPLE_GRAPHICS_COMPONENT_HPP