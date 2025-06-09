#include "Player.h"

#include "algorithm"

Player::Player(int playerId, std::shared_ptr<InputInterpreter> inputInterpreter, IWorldView* worldView)
    : playerId(playerId),
      input(std::move(inputInterpreter)),
      world(worldView),
      health(3), // default values, can be changed
      stock(2), // default values, can be changed
      pos(playerId * 500.0f, playerId * 500.0f), // Default position 
      arrow(0.0f, 1.0f), // Default arrow direction pointing up
      cooldown{0.0f, 0.0f, 0.0f, 0.0f}
{}

void Player::update(float dt) {
    input.update(dt);

    // Handle movement input (example)
    Unit::Vec2D movement = input.getMovement();
    float speed = 690.0f;
    if (input.isHoldingKey(Unit::Input::Focus)) {
        speed = 120.0f;
    }
    pos += movement * dt * speed;
    
    // TO DO: character.update(dt, input);

    updateArrow(dt);
    updateCooldowns(dt);
    updateModifiers(dt);
    updateStatusEffects(dt);
}

// void Player::render(Renderer& renderer) const {
//     character.getGraphicComponent().render(renderer);
// }

void Player::setHealth(int h) {
    health = std::max(0, h);
}

void Player::setStock(int s) {
    stock = std::max(0, s);
}

void Player::setPos(const Unit::Vec2D& position) {
    pos = position;
}

void Player::registerHit() {
    health = std::max(0, health - 1); // Decrease health, clamp at 0
    if (health == 0 && stock > 0) {
        stock--;
    }
}

void Player::applyCooldown(Unit::Move move, float cd) {
    cooldown[static_cast<int>(move)] = cd;
}

void Player::applyStatusEffect() {
    // TO DO: when status effects are implemented, apply them here
}

void Player::applyModifier() {
    // TO DO: When modifiers are implemented, apply them here
}

void Player::roundReset() {
    health = 3;
    for (int i = 0; i < Unit::NUM_MOVES; ++i) {
        applyCooldown(static_cast<Unit::Move>(i), 0.0f);
    }
}

void Player::updateArrow(float dt) {
    Unit::Vec2D direction = world->getPlayer(playerId ^ 1)->getPos() - pos;
    if (direction.magnitude() > 0.01f) {
        Unit::Vec2D targetArrow = direction.normalized();
        // Blend toward the target direction
        float blendFactor = 0.12f;
        arrow = (arrow * (1.0f - blendFactor) + targetArrow * blendFactor).normalized();
        
        float maxAngle = 0.15f; // radians
        float dot = std::clamp(arrow.dot(targetArrow), -1.0f, 1.0f);
        float angleBetween = std::acos(dot);
        if (angleBetween > maxAngle) {
            // Rotate arrow toward targetArrow to be exactly maxAngle away
            // Find orthonormal vector
            Unit::Vec2D axis = { -arrow.y, arrow.x }; // perpendicular to arrow
            float directionSign = (axis.dot(targetArrow) > 0.0f) ? 1.0f : -1.0f;
            float cosA = std::cos(maxAngle);
            float sinA = std::sin(maxAngle) * directionSign;
            // Rotate arrow by maxAngle toward target
            arrow = {
                arrow.x * cosA - arrow.y * sinA,
                arrow.x * sinA + arrow.y * cosA
            };
            arrow = arrow.normalized();
        }
    }
}


void Player::updateCooldowns(float dt) {
    for (float& cd : cooldown) {
        if (cd > 0.0f) {
            cd = std::max(cd - dt, 0.0f);
        }
    }
}

void Player::updateModifiers(float dt) {
    // TO DO: When modifiers are implemented, update them here
}

void Player::updateStatusEffects(float dt) {
    // TO DO: When status effects are implemented, update them here
}



// the big renderer for fun
#include "raylib.h"
void Player::render(Renderer& renderer) const {
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
