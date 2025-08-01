#include "LichOffensiveHandler.hpp"
#include "../../../player/Player.hpp"
#include "../LichGraphicsComponent.hpp"
#include "../bullet/ButterflyThrall.hpp"

LichOffensiveHandler::LichOffensiveHandler(LichGraphicsComponent* graphics)
    : TapHandler(Unit::Move::Offensive), graphics(graphics) {}

void LichOffensiveHandler::tap(bool isFocusing) {
    // graphics->useOffensive();

    Unit::Vec2D pos = player->getPosition();
    if (!isFocusing) {
        Unit::Vec2D arrow = player->getArrow();
        if (arrow.x < 0) pos.x -= 70;
        else pos.x += 70;
    }
    
    auto* thrall = new ButterflyThrall(player, pos);
    player->spawnBullet(std::unique_ptr<Bullet>(thrall));
    thralls.push_back(thrall);
    
    for (auto it = thralls.begin(); it != thralls.end(); ) {
        if (!(*it)) {
            it = thralls.erase(it);
        } else {
            ++it;
        }
    }
    if (thralls.size() > MAX_COUNT) {
        thralls.front()->makeDone();
        thralls.pop_front();
    }

    player->applyImplicitMoveLock();
    player->applyCooldown(Unit::Move::Offensive, COOLDOWN);
    player->applyModifier(Unit::Modifier::MovementModifier, MOVEMENT_MODIFIER_DURATION, MOVEMENT_MODIFIER_VALUE, true);
}