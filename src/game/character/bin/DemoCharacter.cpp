#include "DemoCharacter.hpp"

#include "../priestess/PriestessGraphicsComponent.hpp"

#include "../../IBulletSpawner.hpp"
#include "../../player/Player.hpp"
#include "../../player/InputBufferer.hpp"

#include "../../bullet/CommonBullet.hpp"

#include <cmath>
#include <memory>

constexpr float PI = 3.14159265358979323846f;

DemoCharacter::DemoCharacter() : Character("DemoCharacter", 690.0f, 120.0f, std::make_unique<PriestessGraphicsComponent>()) {}

void DemoCharacter::update(float dt, InputBufferer* input) {

    Unit::Vec2D selfPos = player->getPosition();
    Unit::Vec2D enemyArrow = player->getArrow();
    Unit::Vec2D absoluteArrow = player->getTargetPosition() - player->getPosition();

    // Basic move
    if (input->tryRegister(Unit::Input::Basic) &&
        player->getCooldown(Unit::Move::Basic) < Unit::EPS &&
        player->getLock(Unit::Lock::BasicLock) < Unit::EPS)
    {
        float angleOffset = 10.0f * (PI / 180.0f);
        float radius = 10.0f;
        float baseSpeed = 900.0f;
        float lifetime = 1.6f;
        float startup = 0.15f;

        for (int wave = 0; wave < 2; ++wave) {
            for (int i = -1; i <= 1; ++i) {
                float angle = atan2(enemyArrow.y, enemyArrow.x) + i * angleOffset;
                Unit::Vec2D dir = { cosf(angle), sinf(angle) };
                auto bullet = std::make_unique<CommonBullet>(
                    player->getPlayerId(), selfPos, dir, radius, baseSpeed, startup, lifetime
                );
                player->spawnBullet(std::move(bullet));
            }
        }

        player->applyCooldown(Unit::Move::Basic, 0.3f);
        player->applyLock(Unit::Lock::BasicLock, 0.2f);
        player->applyLock(Unit::Lock::WideLock, 0.2f);
        player->applyLock(Unit::Lock::OffensiveLock, 0.2f);
        player->applyLock(Unit::Lock::DefensiveLock, 0.2f);
    }

    // Wide move
    else if (input->tryRegister(Unit::Input::Wide) &&
             player->getCooldown(Unit::Move::Wide) < Unit::EPS &&
             player->getLock(Unit::Lock::WideLock) < Unit::EPS)
    {
        int count = 12;
        float angle0 = atan2(absoluteArrow.y, absoluteArrow.x);
        float angleStep = 2.0f * PI / count;
        float radius = 15.0f;
        float baseSpeed = 700.0f;
        float lifetime = 1.5f;
        float startup = 0.2f;

        for (int i = 0; i < count; ++i) {
            float angle = angle0 + (i + 0.5f) * angleStep;
            Unit::Vec2D dir = { cosf(angle), sinf(angle) };
            auto bullet = std::make_unique<CommonBullet>(
                player->getPlayerId(), selfPos, dir, radius, baseSpeed, startup, lifetime
            );
            player->spawnBullet(std::move(bullet));
        }

        player->applyCooldown(Unit::Move::Wide, 0.3f);
        player->applyLock(Unit::Lock::BasicLock, 0.2f);
        player->applyLock(Unit::Lock::WideLock, 0.2f);
        player->applyLock(Unit::Lock::OffensiveLock, 0.2f);
        player->applyLock(Unit::Lock::DefensiveLock, 0.2f);
    }

    // Offensive move
    else if (input->tryRegister(Unit::Input::Offensive) &&
             player->getCooldown(Unit::Move::Offensive) < Unit::EPS &&
             player->getLock(Unit::Lock::OffensiveLock) < Unit::EPS)
    {
        float offsetX = 80.0f;
        float spacingY = 40.0f;
        float radius = 10.0f;
        float baseSpeed = 110.0f;
        float lifetime = 1.0f;
        float startup = 0.4f;

        for (int dir = -1; dir <= 1; dir += 2) {
            for (int i = 0; i < 5; ++i) {
                Unit::Vec2D pos = {
                    selfPos.x + dir * offsetX,
                    selfPos.y + (i - 2) * spacingY
                };
                auto bullet = std::make_unique<CommonBullet>(
                    player->getPlayerId(), pos, Unit::Vec2D{float(dir), 0}, radius, baseSpeed, startup, lifetime
                );
                player->spawnBullet(std::move(bullet));
            }
        }

        player->applyCooldown(Unit::Move::Offensive, 1.0f);
        player->applyLock(Unit::Lock::BasicLock, 0.2f);
        player->applyLock(Unit::Lock::WideLock, 0.2f);
        player->applyLock(Unit::Lock::OffensiveLock, 0.2f);
        player->applyLock(Unit::Lock::DefensiveLock, 0.2f);
    }

    // Defensive move
    else if (input->tryRegister(Unit::Input::Defensive) &&
            player->getCooldown(Unit::Move::Defensive) < Unit::EPS &&
            player->getLock(Unit::Lock::DefensiveLock) < Unit::EPS)
    {
        player->applyInvincibility(3.0f);

        player->applyCooldown(Unit::Move::Defensive, 8.0f);
        player->applyLock(Unit::Lock::BasicLock, 0.2f);
        player->applyLock(Unit::Lock::WideLock, 0.2f);
        player->applyLock(Unit::Lock::OffensiveLock, 0.2f);
        player->applyLock(Unit::Lock::DefensiveLock, 0.2f);
    }
}
