#include "DevTool.hpp"
#include "../World.hpp"
#include "../bullet/BulletGraphicsComponent.hpp"

#include <raylib.h>

bool DevTool::hitboxEnabled = false;

DevTool::DevTool(World* world)
    : world(world), timeScale(1.0f)
{
    if (!world) {
        throw std::invalid_argument("DevTool requires a valid World pointer.");
    }
}

void DevTool::update(float dt) {
    if (IsKeyPressed(KEY_F1)) toggleHitbox();
    if (IsKeyPressed(KEY_F2)) toggleInvincibility();
    if (IsKeyPressed(KEY_F3)) resetCooldown();
    if (IsKeyPressed(KEY_F4)) timeDown();
    if (IsKeyPressed(KEY_F5)) timeUp();
}

float DevTool::getTimeScale() const {
    return timeScale;
}

bool DevTool::isHitboxEnabled() {
    return hitboxEnabled;
}

void DevTool::toggleHitbox() {
    hitboxEnabled = !hitboxEnabled;
}

void DevTool::toggleInvincibility() {
    const float INF = 1e9f;
    for (auto& player : world->players) {
        if (player->getInvincibility() > INF / 2) {
            player->applyInvincibility(0, true, true);
        } else {
            player->applyInvincibility(INF, true, true);
        }
    }
}

void DevTool::resetCooldown() {
    for (auto& player : world->players) {
        for (int i = 0; i < Unit::NUM_MOVES; ++i) {
            Unit::Move move = static_cast<Unit::Move>(i);
            player->applyCooldown(move, 0, true);
            player->applyLock(Unit::moveToLock(move), 0, true);
        }
    }
}

void DevTool::timeDown() {
    if (timeScale < 0.251) return;
    timeScale /= 2;
}

void DevTool::timeUp() {
    if (timeScale > 3.9) return;
    timeScale *= 2;
}