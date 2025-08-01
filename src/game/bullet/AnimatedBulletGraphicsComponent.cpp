#include "AnimatedBulletGraphicsComponent.hpp"
#include "Bullet.hpp"
#include <raylib.h>
#include <cmath>

AnimatedBulletGraphicsComponent::AnimatedBulletGraphicsComponent(
    const Bullet* bullet,
    std::vector<const Texture*> anim,
    int fps,
    float texResize)
    : BulletGraphicsComponent(bullet),
      mainAnim(std::move(anim)),
      mainFps(fps),
      mainTexResize(texResize)
{}

void AnimatedBulletGraphicsComponent::addStartup(float startupGradient, std::vector<const Texture*> startupAnim, int startupFps, float startupTexResize) {
    this->startupGradient = std::max(0.05f, startupGradient);
    this->startupAnim = std::move(startupAnim);
    this->startupFps = startupFps;
    this->startupTexResize = startupTexResize;
}

void AnimatedBulletGraphicsComponent::addFlip(bool horizontal, bool vertical) {
    flipH = horizontal;
    flipV = vertical;
}

void AnimatedBulletGraphicsComponent::addRotation(float rps) {
    rotationSpeed = rps * 2.0f * PI; // rps: revolution per second
}

void AnimatedBulletGraphicsComponent::addOpacity(float opacity) {
    opacityScale = std::max(0.0f, std::min(1.0f, opacity));
}

void AnimatedBulletGraphicsComponent::update(float dt) {
    timer += dt;
}

void AnimatedBulletGraphicsComponent::render() const {
    const Texture* tex = nullptr;
    int frame = 0;
    float scale = mainTexResize;
    float rotation = fmod(timer * rotationSpeed, 2.0f * PI) * RAD2DEG;

    float opacity = std::min(timer, startupGradient) / startupGradient;

    if (!startupAnim.empty() && bullet->getDamagingHitbox()) {
        int totalFrames = startupAnim.size();
        frame = static_cast<int>(timer * startupFps) % totalFrames;
        tex = startupAnim[frame];
        scale = startupTexResize;
    } else if (!mainAnim.empty()) {
        int totalFrames = mainAnim.size();
        frame = static_cast<int>(timer * mainFps) % totalFrames;
        tex = mainAnim[frame];
    }
    scale *= bullet->getSize();

    if (tex) {
        Unit::Vec2D pos = bullet->getPosition();
        Rectangle source = { 0, 0, (float)tex->width, (float)tex->height };
        Rectangle dest = { pos.x, pos.y, source.width * scale, source.height * scale };
        Vector2 origin = { dest.width / 2.0f, dest.height / 2.0f };

        if (flipH) source.width *= -1;
        if (flipV) source.height *= -1;

        Color drawColor = WHITE;
        drawColor.a = static_cast<unsigned char>(opacity * opacityScale * 255);

        DrawTexturePro(*tex, source, dest, origin, rotation, drawColor);
    } else {
        std::cerr << "AnimatedBulletGraphicsComponent: No texture to render." << std::endl;
    }

    BulletGraphicsComponent::drawHitboxes();
}