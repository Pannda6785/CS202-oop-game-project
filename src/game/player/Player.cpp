#include "Player.hpp"
#include "../hitbox/CircleHitbox.hpp"
#include "../IWorldView.hpp"

#include <algorithm>
#include <cmath>

Player::Player(int playerId, IWorldView* worldView)
    : playerId(playerId),
      world(worldView),
      hitbox(std::make_unique<CircleHitbox>(pos, 6.0f))
{}

// --- Update methods ---
void Player::init() {
    setPosition({500 + playerId * 500.0f, 300 + playerId * 100.0f});
    arrow = {0.0f, 1.0f};
    stock = 2;
    roundReset();
    applyInvincibility(3.0f, true);
    character->registerPlayer(this);
    character->registerInputBufferer(input.get());
    character->init();
}

void Player::update(float dt) {
    input->update(dt);
    updateMovement(dt);
    hitbox->setPosition(pos);
    updateArrow(dt);
    character->update(dt);
    invincibility = std::max(0.0f, invincibility - dt);
    updateLocks(dt);
    updateModifiers(dt);
    graphics->update(dt);
}

void Player::takeHit() {
    setHealth(health - 1);
    if (health == 0 && stock > 0) {
        stock--;
        roundReset();
    }
    applyInvincibility(3.0f);
    applyModifier(Unit::Modifier::MovementModifier, 2.0f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second, 0.5f);
    applyLock(Unit::Lock::MovementLock, 1.5f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second);
    applyLock(Unit::Lock::BasicLock, 1.6f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second);
    applyLock(Unit::Lock::WideLock, 1.6f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second);
    applyLock(Unit::Lock::OffensiveLock, 1.6f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second);
    applyLock(Unit::Lock::DefensiveLock, 1.6f * modifiers[static_cast<int>(Unit::Modifier::StaggerModifier)].second);
    graphics->takeHit(1.5f); // how long movement lock
}

void Player::confirmHit() {
    applyInvincibility(1.2f);
}

void Player::roundReset() {
    health = 3;
    for (auto& lock : locks) lock = 0.0f;
    for (auto& mod : modifiers) mod = {0.0f, 1.0f};
}

// --- Register components ---
void Player::registerInputInterpreter(std::shared_ptr<InputInterpreter> inputInterpreter) {
    input = std::make_unique<InputBufferer>(inputInterpreter);
    // if (character) {
    //     character->registerInputBufferer(input.get());
    // }
}

void Player::registerCharacter(std::unique_ptr<Character> character) {
    this->character = std::move(character);
    // character->registerPlayer(this);
    // character->setGraphicsComponent(graphics.get());
    // if (input) character->registerInputBufferer(input.get());
}

void Player::registerGraphicsComponent(std::unique_ptr<CharacterGraphicsComponent> graphicsComponent) {
    // it is expected that the character will register the graphics component
    graphics = std::move(graphicsComponent);
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

void Player::setHealth(int h) {
    health = std::max(0, h);
}

void Player::setStock(int s) {
    stock = std::max(0, s);
}

const Hitbox* Player::getHitbox() const {
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
    if (hitbox) hitbox->setPosition(pos);
}

// --- Status data ---
float Player::getInvincibility() const {
    return invincibility;
}

const std::array<std::pair<float, float>, Unit::NUM_MODIFIERS>& Player::getModifiers() const {
    return modifiers;
}

const std::array<float, Unit::NUM_LOCKS>& Player::getLocks() const {
    return locks;
}

void Player::applyInvincibility(float duration, bool force) {
    if (force) {
        invincibility = duration;
    } else {
        invincibility = std::max(invincibility, duration);
    }
}

void Player::applyLock(Unit::Lock lock, float duration, bool force) {
    if (force) {
        locks[static_cast<int>(lock)] = duration;
    } else {
        locks[static_cast<int>(lock)] = std::max(locks[static_cast<int>(lock)], duration);
    }
}

void Player::applyModifier(Unit::Modifier mod, float duration, float value, bool force) {
    // always force, i guess
    modifiers[static_cast<int>(mod)] = {duration, value};
}

// --- Private helpers ---
void Player::updateMovement(float dt) {
    movement = {0.0f, 0.0f};
    float speed = 660;
    // float speed = input->isHoldingKey(Unit::Input::Focus)
    //             ? character->getFocusedSpeed()
    //             : character->getMoveSpeed();
    if (modifiers[static_cast<int>(Unit::Modifier::MovementModifier)].first > 0.0f) {
        speed *= modifiers[static_cast<int>(Unit::Modifier::MovementModifier)].second;
    }
    if (locks[static_cast<int>(Unit::Lock::MovementLock)] > 0.0f) {
        speed = 0;
    }
    movement = input->getMovement() * speed;
    pos += movement * dt;
}

void Player::updateArrow(float dt) {
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

    constexpr float turnSpeedScale = 10.0f;
    float rotateBy = std::min(angleDiff, turnSpeedScale * angleDiff * dt);

    float cosA = std::cos(rotateBy);
    float sinA = std::sin(rotateBy) * direction;

    Unit::Vec2D rotatedArrow = {
        arrow.x * cosA - arrow.y * sinA,
        arrow.x * sinA + arrow.y * cosA
    };

    arrow = rotatedArrow.normalized();
}

void Player::updateLocks(float dt) {
    for (float& lock : locks) {
        if (lock > 0.0f)
            lock = std::max(lock - dt, 0.0f);
    }
}

void Player::updateModifiers(float dt) {
    for (auto& [duration, value] : modifiers) {
        if (duration > 0.0f) {
            duration = std::max(duration - dt, 0.0f);
            if (duration < Unit::EPS) {
                value = 1.0f;
            }
        }
    }
}
