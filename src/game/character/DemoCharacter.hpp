#ifndef DEMO_CHARACTER_HPP
#define DEMO_CHARACTER_HPP

// #include "Character.hpp"
// #include "../bullet/DemoBullet.hpp"

// class DemoCharacter : public Character {
// public:
//     DemoCharacter() {
//         moveSpeed = 660.0f;
//         focusedSpeed = 120.0f;
//         name = "DemoCharacter";
//     }

//     void update(float dt, InputHandler& input) override {
//         if (!player) return;

//         Unit::Vec2D selfPos = player->getPosition();
//         Unit::Vec2D enemyArrow = player->getArrow(); // direction toward enemy

//         // --- Basic Move: Two waves of 3 bullets ---
//         if (input.tryRegister(Unit::Input::Basic) &&
//             player->getCooldown()[static_cast<int>(Unit::Input::Basic)] < Unit::EPS &&
//             player->getLocks()[static_cast<int>(Unit::Lock::BasicLock)] < Unit::EPS)
//         {
//             float angleOffset = 10.0f * (PI / 180.0f); // 10 degrees in radians
//             float baseSpeed = 900.0f;
//             float lifetime = 1.6f;

//             for (int wave = 0; wave < 2; ++wave) {
//                 for (int i = -1; i <= 1; ++i) {
//                     float angle = atan2(enemyArrow.y, enemyArrow.x) + i * angleOffset;
//                     Unit::Vec2D dir = { cosf(angle), sinf(angle) };
//                     auto bullet = std::make_unique<DemoBullet>(player->getId(), selfPos, dir, baseSpeed, lifetime);
//                     player->spawnBullet(std::move(bullet));
//                 }
//             }
//             player->applyCooldown(Unit::Move::Basic, 0.3f);
//             player->applyLock(Unit::Lock::BasicLock, 0.2f);
//             player->applyLock(Unit::Lock::WideLock, 0.2f);
//             player->applyLock(Unit::Lock::OffensiveLock, 0.2f);
//         }
//         // --- Wide Move: 8 bullets in circle with intentional gap ---
//         else if (input.tryRegister(Unit::Input::Wide) &&
//                 player->getCooldown()[static_cast<int>(Unit::Input::Wide)] < Unit::EPS &&
//                 player->getLocks()[static_cast<int>(Unit::Lock::WideLock)] < Unit::EPS)
//         {
//             int count = 12;
//             float angleStep = 2.0f * PI / count;
//             float enemyAngle = atan2(enemyArrow.y, enemyArrow.x);
//             float baseSpeed = 700.0f;
//             float lifetime = 1.5f;

//             for (int i = 0; i < count; ++i) {
//                 float angle = (i + 0.5f) * angleStep;
//                 Unit::Vec2D dir = { cosf(angle), sinf(angle) };
//                 auto bullet = std::make_unique<DemoBullet>(player->getId(), selfPos, dir, baseSpeed, lifetime);
//                 player->spawnBullet(std::move(bullet));
//             }
//             player->applyCooldown(Unit::Move::Wide, 0.3f);
//             player->applyLock(Unit::Lock::BasicLock, 0.2f);
//             player->applyLock(Unit::Lock::WideLock, 0.2f);
//             player->applyLock(Unit::Lock::OffensiveLock, 0.2f);
//         }
//         // --- Offense Move: 2 vertical walls of 5 bullets each ---
//         else if (input.tryRegister(Unit::Input::Offensive) &&
//                 player->getCooldown()[static_cast<int>(Unit::Input::Offensive)] < Unit::EPS &&
//                 player->getLocks()[static_cast<int>(Unit::Lock::OffensiveLock)] < Unit::EPS)
//         {
//             float offsetX = 80.0f;
//             float spacingY = 40.0f;
//             float baseSpeed = 110.0f;
//             float lifetime = 1.0f;

//             for (int dir = -1; dir <= 1; dir += 2) { // Left and right walls
//                 for (int i = 0; i < 5; ++i) {
//                     Unit::Vec2D pos = {
//                         selfPos.x + dir * offsetX,
//                         selfPos.y + (i - 2) * spacingY
//                     };
//                     auto bullet = std::make_unique<DemoBullet>(player->getId(), pos, Unit::Vec2D{dir, 0}, baseSpeed, lifetime);
//                     player->spawnBullet(std::move(bullet));
//                 }
//             }

//             player->applyCooldown(Unit::Move::Offensive, 1.0f);
//             player->applyLock(Unit::Lock::BasicLock, 0.2f);
//             player->applyLock(Unit::Lock::WideLock, 0.2f);
//             player->applyLock(Unit::Lock::OffensiveLock, 0.2f);
//         }
//     }

//     std::string getName() const override {
//         return name;
//     }

//     float getMoveSpeed() const override {
//         return moveSpeed;
//     }

//     float getFocusedSpeed() const override {
//         return focusedSpeed;
//     }

// };

#endif // DEMO_CHARACTER_HPP
