#include "ChargeGraphicsComponent.hpp"
#include "../../../graphics/TextureManager.hpp"
#include "../Bullet.hpp"
#include <raylib.h>
#include <algorithm>
#include <iostream>

ChargeGraphicsComponent::ChargeGraphicsComponent(std::array<int, 4> color, float startRadius, float endRadius, float duration)
    : color(color),
      startRadius(startRadius),
      endRadius(endRadius),
      duration(duration),
      radius(startRadius),
      automatic(true)
{
    setLayer(Unit::Layer::Overlay);
}

ChargeGraphicsComponent::ChargeGraphicsComponent(std::array<int, 4> color)
    : color(color),
      radius(0.0f),
      automatic(false)
{
    setLayer(Unit::Layer::Overlay);
}

void ChargeGraphicsComponent::setRadius(float r) {
    radius = r;
    automatic = false;
}

void ChargeGraphicsComponent::addInner(std::array<int, 4> color, float speed, bool loop) {
    Inner inner = { color, speed, loop, radius, 0.0f };
    inners.push_back(inner);
}

void ChargeGraphicsComponent::update(float dt) {
    time += dt;
    if (automatic) {
        float t = duration > 0.0f ? std::min(time / duration, 1.0f) : 1.0f;
        radius = startRadius + (endRadius - startRadius) * t;
    }
    for (auto& inner : inners) {
        inner.timer += dt;
        inner.radius -= inner.speed * dt;
        if (inner.radius <= 0.0f && inner.loop) {
            inner.radius = radius;
            inner.timer = 0.0f;
        }
    }
}

void ChargeGraphicsComponent::render() const {
    if (!bullet) return;
    Unit::Vec2D pos = bullet->getPosition();
    float scale = bullet->getSize();

    const Texture* tex = TextureManager::instance().getTexture(TEXTURE_PATH);
    if (!tex) return;

    float resize = 2.0f * radius * scale / (VISIBLE_RATIO * TEXTURE_WIDTH);
    Color drawColor = { (unsigned char)color[0], (unsigned char)color[1], (unsigned char)color[2], (unsigned char)color[3] };
    Rectangle source = { 0, 0, (float)tex->width, (float)tex->height };
    Rectangle dest = { pos.x, pos.y, tex->width * resize, tex->height * resize };
    Vector2 origin = { dest.width / 2.0f, dest.height / 2.0f };
    DrawTexturePro(*tex, source, dest, origin, 0.0f, drawColor);

    for (const auto& inner : inners) {
        if (inner.radius <= 0.0f) continue;
        float innerResize = 2.0f * inner.radius * scale / (VISIBLE_RATIO * TEXTURE_WIDTH);
        Color innerColor = { (unsigned char)inner.color[0], (unsigned char)inner.color[1], (unsigned char)inner.color[2], (unsigned char)inner.color[3] };
        Rectangle innerDest = { pos.x, pos.y, tex->width * innerResize, tex->height * innerResize };
        Vector2 innerOrigin = { innerDest.width / 2.0f, innerDest.height / 2.0f };
        DrawTexturePro(*tex, source, innerDest, innerOrigin, 0.0f, innerColor);
    }
}