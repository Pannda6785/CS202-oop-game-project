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
    if (IsKeyPressed(KEY_F6)) clearBullets();
    if (IsKeyPressed(KEY_F7)) log();
    checkFullscreen();
    checkChallenge();
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

void DevTool::clearBullets() {
    for (auto& bullet : world->bullets) {
        bullet->makeDone();
    }
    world->bullets.clear();
    world->pendingBullets.clear();
}

void DevTool::log() {
    std::cout << "Number of Pending bullets: " << world->pendingBullets.size() << "\n";
    std::cout << "Number of Bullets: " << world->bullets.size() << "\n";
    std::cout << "Number of Players: " << world->players.size() << ", they are:\n";
    for (const auto& player : world->players) {
        std::string name = player->getName();
        int health = player->getHealth();
        int stock = player->getStock();
        auto pos = player->getPosition();
        std::cout << "Player: " << name << ", Health: " << health << ", Stock: " << stock
                  << ", Position: " << pos << "\n";
    }
}

#include "../../graphics/GraphicsComponentManager.hpp"
void DevTool::checkFullscreen() {
    if (IsKeyPressed(KEY_F11)) GraphicsComponentManager::instance().toggleFullscreen();
}

#include "../challenge/BomblessMaiden.hpp"
#include "../challenge/TimeskipMaiden.hpp"
#include "../challenge/GiantMaiden.hpp"
#include "../challenge/IronMaiden.hpp"
#include "../challenge/StoneHeartPulsation.hpp"
#include "../challenge/StoneStaticGreen.hpp"
void DevTool::checkChallenge() {
    if (IsKeyPressed(KEY_KP_4)) world->addChallenge(std::make_unique<BomblessMaiden>());
    if (IsKeyPressed(KEY_KP_7)) world->addChallenge(std::make_unique<TimeskipMaiden>());
    if (IsKeyPressed(KEY_KP_5)) world->addChallenge(std::make_unique<GiantMaiden>());
    if (IsKeyPressed(KEY_KP_8)) world->addChallenge(std::make_unique<IronMaiden>());
    if (IsKeyPressed(KEY_KP_6)) world->addChallenge(std::make_unique<StoneHeartPulsation>());
    if (IsKeyPressed(KEY_KP_9)) world->addChallenge(std::make_unique<StoneStaticGreen>());
}
