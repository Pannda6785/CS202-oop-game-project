#include "StunWaveGraphicsComponent.hpp"

#include "../../../bullet/Bullet.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"

#include <raylib.h>
#include <string>
#include <algorithm>

StunWaveGraphicsComponent::StunWaveGraphicsComponent(const Bullet* bullet, float baseRadius, float startup, float bloomTime, float debloom)
    : BulletGraphicsComponent(bullet), timer(0.0f), startup(startup), bloomTime(bloomTime), baseRadius(baseRadius), debloom(debloom)
{
    chargeCircle = TextureManager::instance().getTexture("../assets/sprites/universal/spr_bullet_warning_0_1.png");
    stun[0] = TextureManager::instance().getTexture("../assets/sprites/hero/bullet/stunwave_0.png");
    stun[1] = TextureManager::instance().getTexture("../assets/sprites/hero/bullet/stunwave_1.png");
}

void StunWaveGraphicsComponent::update(float dt) {
    timer += dt;
    if (timer >= startup && timer < debloom) {
        frame = static_cast<int>((timer - startup) * FLASH_FPS) % 2;
    }
}

void StunWaveGraphicsComponent::render() const {
    float radius = baseRadius * bullet->getSize();
    Unit::Vec2D pos = bullet->getPosition();

    // Charging phase: [0, startup - bloomTime)
    if (timer < startup - bloomTime) {
        if (chargeCircle) {
            float scale = (radius * 2.0f) / chargeCircle->width / chargeVisibleRatio;
            Rectangle destRect = { pos.x, pos.y, chargeCircle->width * scale, chargeCircle->height * scale };
            Rectangle srcRect = { 0, 0, (float)chargeCircle->width, (float)chargeCircle->height };
            Vector2 origin = { chargeCircle->width * scale / 2.0f, chargeCircle->height * scale / 2.0f };
            DrawTexturePro(*chargeCircle, srcRect, destRect, origin, 0.0f, Fade(WHITE, 0.5f));
        }
        if (chargeCircle) {
            float shrinkRatio = 1.0f - (timer / (startup - bloomTime));
            float innerRadius = radius * shrinkRatio;
            float scale = (innerRadius * 2.0f) / chargeCircle->width / chargeVisibleRatio;
            Rectangle destRect = { pos.x, pos.y, chargeCircle->width * scale, chargeCircle->height * scale };
            Rectangle srcRect = { 0, 0, (float)chargeCircle->width, (float)chargeCircle->height };
            Vector2 origin = { chargeCircle->width * scale / 2.0f, chargeCircle->height * scale / 2.0f };
            DrawTexturePro(*chargeCircle, srcRect, destRect, origin, 0.0f, Fade(WHITE, 0.5f));
        }
    }
    // Blooming phase: [startup - bloomTime, startup)
    else if (timer < startup) {
        float bloomProgress = (timer - (startup - bloomTime)) / bloomTime;
        if (stun[0]) {
            float scale = (radius * 2.0f) / stun[0]->width * bloomProgress / stunVisibleRatio;
            Rectangle destRect = { pos.x, pos.y, stun[0]->width * scale, stun[0]->height * scale };
            Rectangle srcRect = { 0, 0, (float)stun[0]->width, (float)stun[0]->height };
            Vector2 origin = { stun[0]->width * scale / 2.0f, stun[0]->height * scale / 2.0f };
            DrawTexturePro(*stun[0], srcRect, destRect, origin, 0.0f, Fade(WHITE, 0.8f));
        }
    }
    // Glowing phase: [startup, debloom)
    else if (timer < debloom) {
        if (stun[frame]) {
            float scale = (radius * 2.0f) / stun[frame]->width / stunVisibleRatio;
            Rectangle destRect = { pos.x, pos.y, stun[frame]->width * scale, stun[frame]->height * scale };
            Rectangle srcRect = { 0, 0, (float)stun[frame]->width, (float)stun[frame]->height };
            Vector2 origin = { stun[frame]->width * scale / 2.0f, stun[frame]->height * scale / 2.0f };
            DrawTexturePro(*stun[frame], srcRect, destRect, origin, 0.0f, Fade(WHITE, 0.8f));
        }
    }
    // Shrinking phase: [debloom, debloom + bloomTime)
    else if (timer < debloom + bloomTime) {
        float shrinkProgress = (timer - debloom) / bloomTime;
        float shrinkScale = 1.0f - shrinkProgress;
        int shrinkFrame = frame;
        if (stun[shrinkFrame]) {
            float scale = (radius * 2.0f) / stun[shrinkFrame]->width * shrinkScale / stunVisibleRatio;
            Rectangle destRect = { pos.x, pos.y, stun[shrinkFrame]->width * scale, stun[shrinkFrame]->height * scale };
            Rectangle srcRect = { 0, 0, (float)stun[shrinkFrame]->width, (float)stun[shrinkFrame]->height };
            Vector2 origin = { stun[shrinkFrame]->width * scale / 2.0f, stun[shrinkFrame]->height * scale / 2.0f };
            DrawTexturePro(*stun[shrinkFrame], srcRect, destRect, origin, 0.0f, Fade(WHITE, 0.8f * shrinkScale));
        }
    }

    BulletGraphicsComponent::drawHitboxes();
}