#include "RippleGraphicsComponent.hpp"
#include "../../../graphics/TextureManager.hpp"
#include "../Bullet.hpp"
#include <raylib.h>
#include <algorithm>
#include <cmath>

RippleGraphicsComponent::RippleGraphicsComponent(std::array<int, 4> color, 
    int numRipples, float startRadius, float endRadius, 
    float duration, float frequency, float thickness)
    : numRipples(numRipples),
      startRadius(startRadius),
      endRadius(endRadius),
      duration(duration),
      frequency(frequency),
      thickness(thickness),
      color(color)
{
    setLayer(Unit::Layer::Overlay);
}

void RippleGraphicsComponent::update(float dt) {
    time += dt;
    if (time > duration + (numRipples + 1) * frequency) {
        setVisible(false);
    }
}

void RippleGraphicsComponent::render() const {
    if (!bullet) return;
    Unit::Vec2D pos = bullet->getPosition();
    float scale = bullet->getSize();

    float alphaBase = 1.0f - (time / duration); // fade out over duration

    for (int i = 0; i < numRipples; ++i) {
        float t = (float)i / numRipples;
        float progress = (time / duration) + t;
        if (progress > 1.0f) continue;

        float rippleRadius = (startRadius * 0.97f + (progress * (endRadius - startRadius))) * scale;
        Color ringColor = { 
            (unsigned char)color[0], 
            (unsigned char)color[1], 
            (unsigned char)color[2], 
            (unsigned char)(color[3] * alphaBase * (1.0f - std::pow(t, 2.5)))
        };

        DrawRing(
            { pos.x, pos.y },
            std::max(0.0f, rippleRadius - thickness / 2.0f),
            rippleRadius + thickness / 2.0f,
            0.0f, 360.0f,
            64,
            ringColor
        );
    }
}