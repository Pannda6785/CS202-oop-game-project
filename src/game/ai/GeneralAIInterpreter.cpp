#include "GeneralAIInterpreter.hpp"

#include "../IWorldView.hpp"
#include "../bullet/Bullet.hpp"
#include "../player/Player.hpp"
#include "../hitbox/CircleHitbox.hpp"

#include <algorithm>
#include <random>
#include <cmath>

void GeneralAIInterpreter::update(float dt) {
    auto randomFloat = [&](float a, float b) -> float {
        static std::mt19937 rng{std::random_device{}()};
        std::uniform_real_distribution<float> dist(a, b);
        return dist(rng);
    };

    // Handle action pool and action timing
    if (!currentAction.has_value() || currentAction->elapsedTime >= currentAction->duration) {
        // Weighted random selection
        float totalWeight = 0.0f;
        for (const auto& p : actionPool) totalWeight += p.first;
        float r = randomFloat(0.0f, totalWeight);
        float acc = 0.0f;
        for (const auto& p : actionPool) {
            acc += p.first;
            if (r <= acc) {
                currentAction = p.second;
                currentAction->elapsedTime = 0.0f;
                break;
            }
        }
    }
    if (currentAction.has_value()) {
        currentAction->elapsedTime += dt;
    }

    // Movement logic
    Unit::Vec2D newDir;

    const Player* self = worldView->getPlayer(id);
    Unit::Vec2D pos = self->getPosition();
    Unit::Vec2D battleCenter = Unit::Vec2D(Unit::BATTLEFIELD_WIDTH / 2, Unit::BATTLEFIELD_HEIGHT / 2);
    if ((battleCenter - pos).magnitude() > 300) {
        newDir = (battleCenter - pos).normalized();
    }
    
    if (isBulletThreatening()) {
        newDir = weaveBetweenBullets();
    } else if (isBulletNear()) {
        newDir = getAwayFromBullets();
    }

    // Direction blending logic
    if (std::abs(curDir.x) < Unit::EPS && std::abs(curDir.y) < Unit::EPS) {
        curDir = newDir;
        reverseDirTimer = REVERSE_DIR_TIME;
    } else {
        float dot = curDir.x * newDir.x + curDir.y * newDir.y;
        if (dot > 0.6) {
            curDir = newDir;
            reverseDirTimer = REVERSE_DIR_TIME;
        } else if (dot > 0.2f) {
            // Somewhat aligned, blend
            curDir = ((curDir + newDir + newDir) / 3).normalized();
            reverseDirTimer = REVERSE_DIR_TIME;
        } else {
            // Opposite, keep current for a short time
            reverseDirTimer -= dt;
            if (reverseDirTimer <= 0.0f) {
                curDir = newDir;
            }
        }
    }
}

Unit::Vec2D GeneralAIInterpreter::getMovement() const {
    return curDir;
}

bool GeneralAIInterpreter::isInputPressed(Unit::Input input) const {
    if (!currentAction.has_value()) return false;
    return currentAction->input == input && currentAction->elapsedTime < 0.1f;
}

bool GeneralAIInterpreter::isInputReleased(Unit::Input input) const {
    if (!currentAction.has_value()) return false;
    return currentAction->input == input && currentAction->elapsedTime > currentAction->duration - 0.1f;
}

bool GeneralAIInterpreter::isInputDown(Unit::Input input) const {
    if (!currentAction.has_value()) return false;
    return currentAction->input == input;
}

bool GeneralAIInterpreter::isInputUp(Unit::Input input) const {
    if (!currentAction.has_value()) return true;
    return currentAction->input != input;
}

bool GeneralAIInterpreter::isBulletNear() const {
    // Check if any bullet is within BULLET_NEAR_DISTANCE of any player
    if (!worldView) return false;
    auto bullets = worldView->getBullets();
    auto players = worldView->getPlayers();
    for (const auto* bullet : bullets) {
        Unit::Vec2D bpos = bullet->getPosition();
        for (const auto* player : players) {
            Unit::Vec2D ppos = player->getPosition();
            float dx = bpos.x - ppos.x;
            float dy = bpos.y - ppos.y;
            float distSq = dx * dx + dy * dy;
            if (distSq < BULLET_NEAR_DISTANCE * BULLET_NEAR_DISTANCE)
                return true;
        }
    }
    return false;
}

bool GeneralAIInterpreter::isBulletThreatening() const {
    if (!worldView) return false;
    auto bullets = worldView->getBullets();
    const Player* self = worldView->getPlayer(id);
    Unit::Vec2D selfPos = self->getPosition();

    // Create a local circle hitbox around the player
    CircleHitbox threatZone(selfPos, BULLET_THREAT_DISTANCE);

    for (const auto* bullet : bullets) {
        const Hitbox* dmgHitbox = bullet->getDamagingHitbox();
        if (!dmgHitbox) continue;
        if (threatZone.collidesWith(*dmgHitbox)) {
            return true;
        }
    }
    return false;
}

Unit::Vec2D GeneralAIInterpreter::getAwayFromBullets() const {
    // Move away from the nearest bullet
    if (!worldView) return {0.0f, 0.0f};
    auto bullets = worldView->getBullets();
    const Player* self = worldView->getPlayer(id);
    Unit::Vec2D selfPos = self->getPosition();

    float minDistSq = 1e9f;
    Unit::Vec2D away = {0.0f, 0.0f};
    for (const auto* bullet : bullets) {
        Unit::Vec2D bpos = bullet->getPosition();
        float dx = selfPos.x - bpos.x;
        float dy = selfPos.y - bpos.y;
        float distSq = dx * dx + dy * dy;
        if (distSq < minDistSq) {
            minDistSq = distSq;
            away = {dx, dy};
        }
    }
    float len = std::sqrt(away.x * away.x + away.y * away.y);
    if (len > Unit::EPS)
        return {away.x / len, away.y / len};
    return {0.0f, 0.0f};
}

Unit::Vec2D GeneralAIInterpreter::weaveBetweenBullets() const {
    // Try several directions and use a hitbox to check if that direction is safe
    if (!worldView) return {0.0f, 0.0f};
    auto bullets = worldView->getBullets();
    auto players = worldView->getPlayers();
    if (players.empty()) return {0.0f, 0.0f};
    const Player* self = players.back();
    Unit::Vec2D selfPos = self->getPosition();

    constexpr int NUM_DIRECTIONS = 30;
    constexpr float CHECK_DIST = 20.0f;
    constexpr float PI = 3.14159265358979323846f;

    std::vector<Unit::Vec2D> safeDirs;
    std::vector<float> safeDots;

    for (int i = 0; i < NUM_DIRECTIONS; ++i) {
        float angle = 2.0f * PI * i / NUM_DIRECTIONS;
        Unit::Vec2D dir = { std::cos(angle), std::sin(angle) };
        Unit::Vec2D checkPos = selfPos + dir * CHECK_DIST;

        // Reject direction if it would go outside the battlefield
        if (checkPos.x < 0.0f || checkPos.x > Unit::BATTLEFIELD_WIDTH ||
            checkPos.y < 0.0f || checkPos.y > Unit::BATTLEFIELD_HEIGHT) {
            continue;
        }

        CircleHitbox probe(checkPos, 1.5f);

        bool safe = true;
        for (const auto* bullet : bullets) {
            const Hitbox* dmgHitbox = bullet->getDamagingHitbox();
            if (!dmgHitbox) continue;
            if (probe.collidesWith(*dmgHitbox)) {
                safe = false;
                break;
            }
        }
        if (safe) {
            safeDirs.push_back(dir);
            // Prefer directions most aligned with curDir
            float dot = dir.x * curDir.x + dir.y * curDir.y;
            safeDots.push_back(dot);
        }
    }

    if (!safeDirs.empty()) {
        // Pick the safe direction most aligned with curDir
        auto it = std::max_element(safeDots.begin(), safeDots.end());
        int idx = std::distance(safeDots.begin(), it);
        return safeDirs[idx];
    }

    // If no safe direction, just keep current direction (or fallback to 0,0)
    return curDir;
}