#include "AuraGraphicsComponent.hpp"
#include "../../../graphics/TextureManager.hpp"
#include "../Bullet.hpp"
#include <raylib.h>
#include <algorithm>

AuraGraphicsComponent::AuraGraphicsComponent(std::array<int, 4> color, float startRadius, float endRadius, float duration)
    : startRadius(startRadius),
      endRadius(endRadius),
      duration(duration),
      color(color)
{
    setLayer(Unit::Layer::Overlay);
}

void AuraGraphicsComponent::update(float dt) {
    time += dt;
    if (time > duration) time = duration;
}

void AuraGraphicsComponent::render() const {
    if (!bullet) return;
    Unit::Vec2D pos = bullet->getPosition();
    float t = std::min(time / duration, 1.0f);
    float radius = startRadius + (endRadius - startRadius) * t;
    float scale = bullet->getSize();

    const Texture* tex = TextureManager::instance().getTexture(TEXTURE_PATH);
    float resize = 2.0f * radius * scale / (VISIBLE_RATIO * TEXTURE_WIDTH);
    if (!tex) return;

    Color drawColor = { (unsigned char)color[0], (unsigned char)color[1], (unsigned char)color[2], (unsigned char)color[3] };
    Rectangle source = { 0, 0, (float)tex->width, (float)tex->height };
    Rectangle dest = { pos.x, pos.y, tex->width * resize, tex->height * resize };
    Vector2 origin = { dest.width / 2.0f, dest.height / 2.0f };

    DrawTexturePro(*tex, source, dest, origin, 0.0f, drawColor);
}