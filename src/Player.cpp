#include "Player.h"

#include <algorithm>
#include <cmath>
#include <raylib.h>

Player::Player(int playerId,
               std::unique_ptr<Character> character,
               std::shared_ptr<InputInterpreter> inputInterpreter,
               IWorldView* worldView,
               IBulletSpawner* bulletSpawner)
    : playerId(playerId),
      character(std::move(character)),
      input(std::make_unique<InputHandler>(std::move(inputInterpreter))),
      world(worldView),
      bulletSpawner(bulletSpawner),
      health(3),
      stock(2),
      pos(500 + playerId * 500.0f, 300 + playerId * 500.0f),
      hitbox(pos, 16.0f),
      arrow(0.0f, 1.0f)
{
    this->character->registerPlayer(this);
    roundReset();
}

void Player::update(float dt) {
    input->update(dt);

    Unit::Vec2D movement = input->getMovement();
    float speed = input->isHoldingKey(Unit::Input::Focus)
                    ? character->getFocusedSpeed()
                    : character->getMoveSpeed();
    pos += movement * dt * speed;
    hitbox.setPosition(pos);

    character->update(dt, *input);

    updateArrow(dt);
    updateCooldowns(dt);
    updateStatusEffects(dt);
    updateLocks(dt);
    updateModifiers(dt);
}

void Player::render(Renderer& renderer) const {
    _render(renderer); // TO DO: Delegate this to character's graphics component
}

// --- Life related ---
void Player::setHealth(int h) {
    health = std::max(0, h);
}

void Player::setStock(int s) {
    stock = std::max(0, s);
}

int Player::getHealth() const {
    return health;
}

int Player::getStock() const {
    return stock;
}

const Hitbox* Player::getHitbox() const {
    return &hitbox;
}

std::string Player::getCharacterName() const {
    return character->getName();
}

void Player::registerHit() {
    health = std::max(0, health - 1);
    if (health == 0 && stock > 0) {
        stock--;
    }
}

void Player::roundReset() {
    health = 3;
    for (auto& cd : cooldown) cd = 0.0f;
    for (auto& se : statusEffects) se = 0.0f;
    for (auto& lock : locks) lock = 0.0f;
    for (auto& mod : modifierValues) mod = {0.0f, 1.0f};
}

// --- Exposed Interface ---
int Player::getId() const {
    return playerId;
}

Unit::Vec2D Player::getPosition() const {
    return pos;
}

Unit::Vec2D Player::getArrow() const {
    return arrow;
}

const std::array<float, Unit::NUM_MOVES>& Player::getCooldown() const {
    return cooldown;
}

const std::array<float, Unit::NUM_STATUS_EFFECTS>& Player::getStatusEffects() const {
    return statusEffects;
}

const std::array<float, Unit::NUM_LOCKS>& Player::getLocks() const {
    return locks;
}

void Player::spawnBullet(std::unique_ptr<Bullet> bullet) {
    bulletSpawner->spawnBullet(std::move(bullet));
}

void Player::setPosition(const Unit::Vec2D& position) {
    pos = position;
}

void Player::applyCooldown(Unit::Move move, float duration) {
    cooldown[static_cast<int>(move)] = duration;
}

void Player::applyStatusEffect(Unit::StatusEffect effect, float duration) {
    statusEffects[static_cast<int>(effect)] = duration;
}

void Player::applyLock(Unit::Modifier mod, float duration) {
    locks[static_cast<int>(mod)] = duration;
}

void Player::applyModifier(Unit::Modifier mod, float duration, float value) {
    modifierValues[static_cast<int>(mod)] = {duration, value};
}

// --- Private Helpers ---
void Player::updateArrow(float dt) {
    Unit::Vec2D targetPos = world->getPlayer(playerId ^ 1)->getPosition();
    Unit::Vec2D dir = targetPos - pos;

    if (dir.magnitude() > 0.01f) {
        Unit::Vec2D targetDir = dir.normalized();

        float dot = std::clamp(arrow.dot(targetDir), -1.0f, 1.0f);
        float angleToTarget = std::acos(dot);

        if (angleToTarget < 0.001f)
            return;

        // Rotation direction (2D cross product)
        float cross = arrow.x * targetDir.y - arrow.y * targetDir.x;
        float turnDirection = (cross > 0) ? 1.0f : -1.0f;

        // Dynamic max turn speed: proportional to angle difference, with limits
        constexpr float minTurnSpeed = 2.0f;    // radians/sec, minimal guaranteed speed
        constexpr float maxTurnSpeed = 10.0f;   // max speed arrow can turn
        // Increase turn speed when angle is bigger, else use minimal
        float dynamicTurnSpeed = std::clamp(angleToTarget * 8.0f, minTurnSpeed, maxTurnSpeed);

        // How much we can turn this frame
        float maxAngleThisFrame = dynamicTurnSpeed * dt;
        float rotateBy = std::min(angleToTarget, maxAngleThisFrame);

        float cosA = std::cos(rotateBy);
        float sinA = std::sin(rotateBy) * turnDirection;

        Unit::Vec2D newArrow = {
            arrow.x * cosA - arrow.y * sinA,
            arrow.x * sinA + arrow.y * cosA
        };

        // Smoothly blend toward the new arrow direction to avoid jitter
        constexpr float smoothing = 10.0f; // responsiveness for interpolation
        arrow = (newArrow * (1.0f - dt * smoothing) + targetDir * dt * smoothing).normalized();
    }
}


void Player::updateCooldowns(float dt) {
    for (float& cd : cooldown) {
        if (cd > 0.0f)
            cd = std::max(cd - dt, 0.0f);
    }
}

void Player::updateStatusEffects(float dt) {
    for (float& se : statusEffects) {
        if (se > 0.0f)
            se = std::max(se - dt, 0.0f);
    }
}

void Player::updateLocks(float dt) {
    for (float& lock : locks) {
        if (lock > 0.0f)
            lock = std::max(lock - dt, 0.0f);
    }
}

void Player::updateModifiers(float dt) {
    for (auto& [duration, value] : modifierValues) {
        if (duration > 0.0f) {
            duration = std::max(duration - dt, 0.0f);
            if (duration == 0.0f) {
                value = 1.0f; // Reset to neutral modifier
            }
        }
    }
}

// the big renderer for fun
#include "raylib.h"
void Player::_render(Renderer& renderer) const {
    Vector2 center = { pos.x, pos.y };

    // Draw player base with subtle glow (3 layered circles)
    Color baseColor = playerId == 0 ? BLUE : RED;
    DrawCircleV(center, 22, Fade(baseColor, 0.3f));
    DrawCircleV(center, 18, Fade(baseColor, 0.7f));
    DrawCircleV(center, 16, baseColor);

    // Draw arrow line
    Vector2 arrowEnd = { pos.x + arrow.x * 40, pos.y + arrow.y * 40 };
    DrawLineEx(center, arrowEnd, 3.0f, RED);

    // Draw arrowhead (triangle)
    Vector2 perp = { -arrow.y, arrow.x };  // perpendicular vector
    Vector2 tip = arrowEnd;
    Vector2 baseLeft = { tip.x - arrow.x * 10 + perp.x * 5, tip.y - arrow.y * 10 + perp.y * 5 };
    Vector2 baseRight = { tip.x - arrow.x * 10 - perp.x * 5, tip.y - arrow.y * 10 - perp.y * 5 };
    Vector2 points[3] = { tip, baseLeft, baseRight };
    DrawTriangle(points[0], points[1], points[2], RED);

    // Draw Player ID & Character name above player
    std::string label = TextFormat("P%d: %s", playerId + 1, getCharacterName().c_str());
    DrawText(label.c_str(), static_cast<int>(pos.x - MeasureText(label.c_str(), 12) / 2), static_cast<int>(pos.y - 60), 12, baseColor);

    // Draw health as hearts below player
    const float heartSpacing = 22;
    for (int i = 0; i < 3; ++i) {
        Vector2 heartPos = { pos.x - heartSpacing + i * heartSpacing, pos.y + 40 };
        if (i < health) {
            DrawText("<3", static_cast<int>(heartPos.x), static_cast<int>(heartPos.y), 20, RED);
        } else {
            DrawText("</3", static_cast<int>(heartPos.x), static_cast<int>(heartPos.y), 20, DARKGRAY);
        }
    }

    // Draw stock as small blue circles below hearts
    const float stockRadius = 6;
    for (int i = 0; i < stock; ++i) {
        Vector2 stockPos = { pos.x - heartSpacing + i * heartSpacing, pos.y + 65 };
        DrawCircleV(stockPos, stockRadius, BLUE);
        DrawCircleLines(static_cast<int>(stockPos.x), static_cast<int>(stockPos.y), stockRadius, DARKBLUE);
    }

    // Draw cooldown bars below stock
    const float barWidth = 40;
    const float barHeight = 6;
    const float barSpacing = 10;
    Vector2 barsStart = { pos.x - barWidth / 2, pos.y + 80 };

    for (size_t i = 0; i < cooldown.size(); ++i) {
        float cdRatio = cooldown[i] / 5.0f; // assuming max cooldown ~5s (adjust if needed)
        cdRatio = std::clamp(cdRatio, 0.0f, 1.0f);

        Vector2 barPos = { barsStart.x, barsStart.y + static_cast<float>(i) * (barHeight + barSpacing) };

        // Draw background
        DrawRectangleRec({barPos.x, barPos.y, barWidth, barHeight}, DARKGRAY);

        // Draw foreground cooldown progress
        DrawRectangleRec({barPos.x, barPos.y, barWidth * (1.0f - cdRatio), barHeight}, LIME);

        // Optional: draw move index number inside bar for debug
        std::string moveIdx = std::to_string(i);
        DrawText(moveIdx.c_str(), static_cast<int>(barPos.x + barWidth / 2 - 4), static_cast<int>(barPos.y + 1), 10, BLACK);
    }
}