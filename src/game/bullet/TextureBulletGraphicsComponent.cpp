#include "TextureBulletGraphicsComponent.hpp"
#include "Bullet.hpp"
#include <raylib.h>
#include <cmath>
#include <algorithm>
#include <iostream>

TextureBulletGraphicsComponent::TextureBulletGraphicsComponent(const Texture* tex, float texResize)
    : mainAnim{tex},
      mainFps(1),
      mainTexResize(texResize)
{}

TextureBulletGraphicsComponent::TextureBulletGraphicsComponent(std::vector<const Texture*> anim, int fps, float texResize)
    : mainAnim(std::move(anim)),
      mainFps(fps),
      mainTexResize(texResize)
{}

void TextureBulletGraphicsComponent::addStartup(const Texture* startupTex, float startupTexResize) {
    startupAnim = {startupTex};
    startupFps = 1;
    this->startupTexResize = startupTexResize;
}

void TextureBulletGraphicsComponent::addStartup(std::vector<const Texture*> startupAnim, int startupFps, float startupTexResize) {
    this->startupAnim = std::move(startupAnim);
    this->startupFps = startupFps;
    this->startupTexResize = startupTexResize;
}

void TextureBulletGraphicsComponent::addFadein(float timeStart, float timeEnd) {
    fadeinStart = timeStart;
    fadeinEnd = timeEnd;
}

void TextureBulletGraphicsComponent::addFadeout(float timeStart, float timeEnd) {
    fadeoutStart = timeStart;
    fadeoutEnd = timeEnd;
}

void TextureBulletGraphicsComponent::addBloom(float timeStart, float timeEnd) {
    bloomStart = timeStart;
    bloomEnd = timeEnd;
}

void TextureBulletGraphicsComponent::addDebloom(float timeStart, float timeEnd) {
    debloomStart = timeStart;
    debloomEnd = timeEnd;
}

void TextureBulletGraphicsComponent::addVelocityRotation(bool b) {
    useVelocityMode = b;
}

void TextureBulletGraphicsComponent::addRotation(float rps) {
    rotationSpeed = rps * 2.0f * PI;
}

void TextureBulletGraphicsComponent::addFlip(bool horizontal, bool vertical) {
    flipH = horizontal;
    flipV = vertical;
}

void TextureBulletGraphicsComponent::addTint(std::array<int, 4> tint) {
    this->tint = tint;
}

void TextureBulletGraphicsComponent::update(float dt) {
    time += dt;
}

void TextureBulletGraphicsComponent::render() const {
    if (!bullet) {
        std::cerr << "Warning: TextureBulletGraphicsComponent - Bullet not registered." << std::endl;
        return;
    }

    // Texture selecting selection
    const Texture* tex = nullptr;
    float scale = bullet->getSize();
    if (!startupAnim.empty() && !bullet->getDamagingHitbox()) {
        int totalFrames = startupAnim.size();
        int frame = static_cast<int>(time * startupFps) % totalFrames;
        tex = startupAnim[frame];
        scale *= startupTexResize;
    } else if (!mainAnim.empty()) {
        int totalFrames = mainAnim.size();
        int frame = static_cast<int>(time * mainFps) % totalFrames;
        tex = mainAnim[frame];
        scale *= mainTexResize;
    }

    // Rotation
    float rotation = 0.0f;
    if (useVelocityMode) {
        Unit::Vec2D velocity = bullet->getVelocity();
        if (velocity.x != 0.0f || velocity.y != 0.0f) {
            rotation = std::atan2(velocity.y, velocity.x) * RAD2DEG + 90.0f;
        }
    }
    rotation += fmod(time * rotationSpeed, 2.0f * PI) * RAD2DEG;

    // Opacity calculation (fadein/fadeout)
    float opacity = 1.0f;
    if (time < fadeinStart) {
        opacity *= 0.0f; 
    } else if (time < fadeinEnd) {
        opacity *= (time - fadeinStart) / (fadeinEnd - fadeinStart);
    } else if (time > fadeoutStart && time < fadeoutEnd) {
        opacity *= 1.0f - (time - fadeoutStart) / (fadeoutEnd - fadeoutStart);
    } else if (time >= fadeoutEnd) {
        opacity *= 0.0f;
    } 
    if (madeDone) {
        float factor = 1 - std::min(1.0f, std::max(0.0f, (time - whenMadeDone) / howLongAfterMadeDone));
        opacity *= factor;
    }

    // Bloom/debloom
    if (time < bloomStart) {
        scale *= 0.0f;
    } else if (time < bloomEnd) {
        scale *= (time - bloomStart) / (bloomEnd - bloomStart);
    } else if (time > debloomStart && time < debloomEnd) {
        scale *= 1.0f - (time - debloomStart) / (debloomEnd - debloomStart);
    } else if (time >= debloomEnd) {
        scale *= 0.0f;
    }
    if (madeDone) {
        float progress = std::min(1.0f, std::max(0.0f, (time - whenMadeDone) / howLongAfterMadeDone));
        // maxFactor is 0 for big bullet and 1.8 for small bullet, is a spectrum for [50, 150]
        float size = tex->width * scale;
        float maxFactor = 1.8f * (1.0f - std::min(1.0f, (size - 50.0f) / 100.0f));
        scale *= 1.0f + maxFactor * progress;
    }

    // Render the texture
    if (tex) {
        if (scale > Unit::EPS) {
            Unit::Vec2D pos = bullet->getPosition();
            Rectangle source = { 0, 0, (float)tex->width, (float)tex->height };
            Rectangle dest = { pos.x, pos.y, source.width * scale, source.height * scale };
            Vector2 origin = { dest.width / 2.0f, dest.height / 2.0f };
    
            if (flipH) source.width *= -1;
            if (flipV) source.height *= -1;
    
            Color drawColor = {static_cast<unsigned char>(tint[0]),
                               static_cast<unsigned char>(tint[1]),
                               static_cast<unsigned char>(tint[2]),
                               static_cast<unsigned char>(tint[3])};
            drawColor.a = static_cast<unsigned char>(opacity * drawColor.a);
    
            DrawTexturePro(*tex, source, dest, origin, rotation, drawColor);
        } else {
            std::cerr << "Inform: TextureBulletGraphicsComponent - Texture size is too small to render." << std::endl;
        }
    } else {
        std::cerr << "Warning: TextureBulletGraphicsComponent - No texture to render." << std::endl;
    }

    BulletGraphicsComponent::drawHitboxes();
}

void TextureBulletGraphicsComponent::makeDone() {
    BulletGraphicsComponent::makeDone();
    if (madeDone) return;
    madeDone = true;
    whenMadeDone = time;
}