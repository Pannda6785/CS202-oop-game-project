#include "NoviFireGraphicsComponent.hpp"

#include "../../../bullet/Bullet.hpp"
#include "../../../hitbox/CircleHitbox.hpp"
#include "../../../../graphics/TextureManager.hpp"

#include <raylib.h>
#include <string>
#include <algorithm>

NoviFireGraphicsComponent::NoviFireGraphicsComponent(const Bullet* bullet, float baseRadius, float startup, float bloomTime, float debloom)
    : BulletGraphicsComponent(bullet), timer(0.0f), startup(startup), bloomTime(bloomTime), baseRadius(baseRadius), debloom(debloom)
{
    chargeCircle = TextureManager::instance().getTexture("../assets/sprites/universal/spr_bullet_warning_0_1.png");
    novi[0] = TextureManager::instance().getTexture("../assets/sprites/wyrm/bullet/nidhogg_bullet_1_p1_0000.png");
    novi[1] = TextureManager::instance().getTexture("../assets/sprites/wyrm/bullet/nidhogg_bullet_1_p1_0001.png");
}

void NoviFireGraphicsComponent::update(float dt) {
    timer += dt;
    if (timer >= startup && timer < debloom) {
        frame = static_cast<int>((timer - startup) * FLASH_FPS) % 2;
    }
}

void NoviFireGraphicsComponent::render() const {
    float radius = baseRadius * bullet->getSize();
    Unit::Vec2D pos = bullet->getPosition();

    // Charging phase: [0, startup - bloomTime)
    if (timer < startup - bloomTime) {
        // Outer static charge circle
        if (chargeCircle) {
            float scale = (radius * 2.0f) / chargeCircle->width / chargeVisibleRatio;
            Rectangle destRect = { pos.x, pos.y, chargeCircle->width * scale, chargeCircle->height * scale };
            Rectangle srcRect = { 0, 0, (float)chargeCircle->width, (float)chargeCircle->height };
            Vector2 origin = { chargeCircle->width * scale / 2.0f, chargeCircle->height * scale / 2.0f };
            DrawTexturePro(*chargeCircle, srcRect, destRect, origin, 0.0f, Fade(WHITE, 0.5f));
        }
        // Inner shrinking charge circle
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
        if (novi[0]) {
            float scale = (radius * 2.0f) / novi[0]->width * bloomProgress / noviVisibleRatio;
            Rectangle destRect = { pos.x, pos.y, novi[0]->width * scale, novi[0]->height * scale };
            Rectangle srcRect = { 0, 0, (float)novi[0]->width, (float)novi[0]->height };
            Vector2 origin = { novi[0]->width * scale / 2.0f, novi[0]->height * scale / 2.0f };
            DrawTexturePro(*novi[0], srcRect, destRect, origin, 0.0f, Fade(WHITE, 0.8f));
        }
    }
    // Glowing phase: [startup, debloom)
    else if (timer < debloom) {
        if (novi[frame]) {
            float scale = (radius * 2.0f) / novi[frame]->width / noviVisibleRatio;
            Rectangle destRect = { pos.x, pos.y, novi[frame]->width * scale, novi[frame]->height * scale };
            Rectangle srcRect = { 0, 0, (float)novi[frame]->width, (float)novi[frame]->height };
            Vector2 origin = { novi[frame]->width * scale / 2.0f, novi[frame]->height * scale / 2.0f };
            DrawTexturePro(*novi[frame], srcRect, destRect, origin, 0.0f, Fade(WHITE, 0.8f));
        }
    }
    // Shrinking phase: [debloom, debloom + bloomTime)
    else if (timer < debloom + bloomTime) {
        float shrinkProgress = (timer - debloom) / bloomTime;
        float shrinkScale = 1.0f - shrinkProgress;
        int shrinkFrame = frame;
        if (novi[shrinkFrame]) {
            float scale = (radius * 2.0f) / novi[shrinkFrame]->width * shrinkScale / noviVisibleRatio;
            Rectangle destRect = { pos.x, pos.y, novi[shrinkFrame]->width * scale, novi[shrinkFrame]->height * scale };
            Rectangle srcRect = { 0, 0, (float)novi[shrinkFrame]->width, (float)novi[shrinkFrame]->height };
            Vector2 origin = { novi[shrinkFrame]->width * scale / 2.0f, novi[shrinkFrame]->height * scale / 2.0f };
            DrawTexturePro(*novi[shrinkFrame], srcRect, destRect, origin, 0.0f, Fade(WHITE, 0.8f * shrinkScale));
        }
    }

    BulletGraphicsComponent::drawHitboxes();
}