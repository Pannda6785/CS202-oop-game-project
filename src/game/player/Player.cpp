#include "Player.hpp"

#include "../IWorldView.hpp"
#include "../IBulletSpawner.hpp"
#include "../bullet/Bullet.hpp"

#include "../character/CharacterGraphicsComponent.hpp"

#include <algorithm>
#include <cmath>
#include <random>

Player::Player(int playerId, IWorldView* worldView, IBulletSpawner* bulletSpawner,
            std::unique_ptr<Character> character, std::shared_ptr<InputInterpreter> inputInterpreter) 
        : playerId(playerId), world(worldView), bulletSpawner(bulletSpawner), 
          character(std::move(character)), input(std::make_unique<InputBufferer>(inputInterpreter)) 
{
    this->character->registerPlayer(this);

    health = 3;
    stock = 2;
    invincibility = {0, 0};

    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> distX(0, Unit::BATTLEFIELD_WIDTH);
    std::uniform_real_distribution<float> distY(0, Unit::BATTLEFIELD_HEIGHT);
    setPosition({distX(gen), distY(gen)});
    
    arrow = {0.0f, 1.0f};
    movement = {0.0f, 0.0f};
    
    hitbox = std::make_unique<CircleHitbox>(pos, HITBOX_RADIUS);
}

// --- Update methods ---
void Player::init() {
    character->init();
    
    for (auto& lock : locks) lock = 0.0f;
    for (auto& mod : modifiers) mod = {0.0f, 1.0f};
    for (auto& cd : cooldown) cd = 0.0f;
    applyInvincibility(3.0f, true);
}

void Player::update(float dt) {
    input->update(dt);
    updateMovement(dt);
    updateArrow(dt);
    updateStatus(dt);
    character->update(dt, input.get());
    character->getGraphics()->update(dt);
}

void Player::takeHit() {
    health = std::max(health - 1, 0);
    if (health == 0 && stock > 0) stock--;

    applyInvincibility(3.0f, true);
    applyModifier(Unit::Modifier::MovementModifier, 2.0f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second, 0.5f);
    applyLock(Unit::Lock::MovementLock, 1.5f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second);
    applyLock(Unit::Lock::BasicLock, 1.6f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second);
    applyLock(Unit::Lock::WideLock, 1.6f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second);
    applyLock(Unit::Lock::OffensiveLock, 1.6f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second);
    applyLock(Unit::Lock::DefensiveLock, 1.6f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second);
    character->getGraphics()->takeHit(1.7f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second); // how long movement lock
}

void Player::confirmHit() {
    applyInvincibility(1.2f, false);
}

void Player::roundReset() {
    health = 3;
    for (auto& lock : locks) lock = 0.0f;
    for (auto& mod : modifiers) mod = {0.0f, 1.0f};
}

// --- World interaction ---

const IWorldView* Player::getWorld() const {
    return world;
}

void Player::spawnBullet(std::shared_ptr<Bullet> bullet) {
    bullet->resize(modifiers[static_cast<int>(Unit::Modifier::BulletSizeModifier)].second);
    bulletSpawner->spawnBullet(move(bullet));
}

// --- Life data ---
int Player::getPlayerId() const {
    return playerId;
}

int Player::getHealth() const {
    return health;
}

int Player::getStock() const {
    return stock;
}

const CircleHitbox* Player::getHitbox() const {
    return hitbox.get();
}

// --- Positional data ---
Unit::Vec2D Player::getPosition() const {
    return pos;
}

Unit::Vec2D Player::getArrow() const {
    return arrow;
}

Unit::Vec2D Player::getMovement() const {
    return movement;
}

Unit::Vec2D Player::getTargetPosition() const {
    const Player* otherPlayer = world->getPlayer(playerId ^ 1);
    if (otherPlayer) {
        return otherPlayer->getPosition();
    } else {
        return {Unit::BATTLEFIELD_WIDTH / 2.0f, Unit::BATTLEFIELD_HEIGHT / 2.0f};
    }
}

void Player::setPosition(const Unit::Vec2D& newPos) {
    pos = newPos;
    pos.x = std::clamp(pos.x, 0.0f, Unit::BATTLEFIELD_WIDTH);
    pos.y = std::clamp(pos.y, 0.0f, Unit::BATTLEFIELD_HEIGHT);
}

// --- Status data ---
float Player::getInvincibility(bool major) const {
    if (major) return invincibility[major];
    return std::max(invincibility[0], invincibility[1]);
}

std::pair<float, float> Player::getModifier(Unit::Modifier mod) const {
    return modifiers[static_cast<int>(mod)];
}

float Player::getLock(Unit::Lock lock) const {
    return locks[static_cast<int>(lock)];
}

float Player::getCooldown(Unit::Move move) const {
    return cooldown[static_cast<int>(move)];
}

void Player::applyInvincibility(float duration, bool major, bool force) {
    if (force) {
        invincibility[0] = invincibility[1] = duration;
    } else {
        invincibility[major] = std::max(invincibility[major], duration);
    }
}

void Player::applyModifier(Unit::Modifier mod, float duration, float value, bool force) {
    if (force) {
        modifiers[static_cast<int>(mod)] = {duration, value};
    } else {
        // only if the previous duration is very long should the previous effect be continued
        if (modifiers[static_cast<int>(mod)].first < 1000) {
            modifiers[static_cast<int>(mod)] = {duration, value};
        }
    }
}

void Player::applyLock(Unit::Lock lock, float duration, bool force) {
    duration *= modifiers[static_cast<int>(Unit::Modifier::CooldownModifier)].second;
    if (force) {
        locks[static_cast<int>(lock)] = duration;
    } else {
        locks[static_cast<int>(lock)] = std::max(locks[static_cast<int>(lock)], duration);
    }
}

void Player::applyCooldown(Unit::Move move, float duration, bool force) {
    duration *= modifiers[static_cast<int>(Unit::Modifier::CooldownModifier)].second;
    if (force) {
        cooldown[static_cast<int>(move)] = duration;
    } else {
        cooldown[static_cast<int>(move)] = std::max(cooldown[static_cast<int>(move)], duration);
    }
}

void Player::applyImplicitMoveLock(bool force) {
    applyLock(Unit::Lock::BasicLock, 0.2f, force);
    applyLock(Unit::Lock::WideLock, 0.2f, force);
    applyLock(Unit::Lock::OffensiveLock, 0.2f, force);
    applyLock(Unit::Lock::DefensiveLock, 0.2f, force);
}

// --- Export data ---
std::string Player::getName() const {
    return character->getName();
}

std::array<int, 4> Player::getSignatureColor() const {
    return character->getGraphics()->getSignatureColor();
}

// --- Private helpers ---
void Player::updateMovement(float dt) {
    movement = {0.0f, 0.0f};
    float speed = input->isHoldingKey(Unit::Input::Focus)
                ? character->getFocusedSpeed()
                : character->getMoveSpeed();
    if (modifiers[static_cast<int>(Unit::Modifier::MovementModifier)].first > 0.0f) {
        speed *= modifiers[static_cast<int>(Unit::Modifier::MovementModifier)].second;
    }
    if (locks[static_cast<int>(Unit::Lock::MovementLock)] > Unit::EPS) {
        speed = 0;
    }
    movement = input->getMovement() * speed;
    setPosition(pos + movement * dt);

    hitbox->setPosition(pos);
}

void Player::updateArrow(float dt) {
    if (locks[static_cast<int>(Unit::Lock::ArrowLock)] > Unit::EPS) {
        return;
    }

    Unit::Vec2D targetPos = getTargetPosition();
    Unit::Vec2D toTarget = targetPos - pos;

    if (toTarget.magnitude() < Unit::EPS) {
        return;
    }

    Unit::Vec2D targetDir = toTarget.normalized();
    float dot = std::clamp(arrow.dot(targetDir), -1.0f, 1.0f);
    float angleDiff = std::acos(dot);

    constexpr float maxAngleOffset = 1.0f;
    if (angleDiff > maxAngleOffset) {
        float cross = arrow.x * targetDir.y - arrow.y * targetDir.x;
        float direction = (cross > 0) ? 1.0f : -1.0f;

        float cosA = std::cos(maxAngleOffset);
        float sinA = std::sin(maxAngleOffset) * direction;

        Unit::Vec2D clampedArrow = {
            targetDir.x * cosA - targetDir.y * sinA,
            targetDir.x * sinA + targetDir.y * cosA
        };

        arrow = clampedArrow.normalized();
        return;
    }

    float cross = arrow.x * targetDir.y - arrow.y * targetDir.x;
    float direction = (cross > 0) ? 1.0f : -1.0f;

    float turnSpeedScale = input->isHoldingKey(Unit::Input::Focus) ? 15.0f : 10.0f;
    turnSpeedScale *= modifiers[static_cast<int>(Unit::Modifier::ArrowModifier)].second;
    float rotateBy = std::min(angleDiff, turnSpeedScale * angleDiff * dt);

    float cosA = std::cos(rotateBy);
    float sinA = std::sin(rotateBy) * direction;

    Unit::Vec2D rotatedArrow = {
        arrow.x * cosA - arrow.y * sinA,
        arrow.x * sinA + arrow.y * cosA
    };

    arrow = rotatedArrow.normalized();
}

void Player::updateStatus(float dt) {
    invincibility[0] = std::max(0.0f, invincibility[0] - dt);
    invincibility[1] = std::max(0.0f, invincibility[1] - dt);

    for (auto& [duration, value] : modifiers) {
        if (duration > 0.0f) {
            duration = std::max(duration - dt, 0.0f);
        }
        if (duration < Unit::EPS) {
            value = 1.0f;
        }
    }

    for (float& lock : locks) {
        if (lock > 0.0f)
            lock = std::max(lock - dt, 0.0f);
    }

    for (float& cd : cooldown) {
        if (cd > 0.0f) 
            cd = std::max(cd - dt, 0.0f);
    }

    float scale = modifiers[static_cast<int>(Unit::Modifier::SizeModifier)].second;
    float shouldBeRadius = HITBOX_RADIUS * scale;
    hitbox->resize(shouldBeRadius / hitbox->getRadius());
    character->getGraphics()->resize(scale / character->getGraphics()->getSize());
}

