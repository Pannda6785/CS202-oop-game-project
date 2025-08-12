#include "World.hpp"

#include <algorithm>
#include <iostream>

#include "../UI/game_state/versus_mode_state/HUD/hot_bar/sun_priestess_hot_bar/SunPriestessHotBar.hpp"

World::World() : devTool(nullptr), combatFeedbackManager(), leftHotBar(nullptr) {
}

// World::World() : devTool(nullptr), combatFeedbackManager() {
// }

void World::update(float dt) {
    if(freezeTimer > 0.0f) {
        freezeTimer -= dt;
        if (freezeTimer <= 0.0f) {
            freezeTimer = 0.0f;
        }
        return;
    }
    devTool->update(dt);
    dt *= devTool->getTimeScale();
    if (dt < Unit::EPS) return;
    
    for (auto& player : players) {
        player->update(dt);
    }
    for (auto& pattern : patterns) {
        pattern->update(dt);
    }
    for (auto& bullet : bullets) {
        bullet->update(dt);
    }
    handlePendings(dt);
    handleCollisions();
    combatFeedbackManager.update(dt);
    if (leftHotBar) {
        std::vector<float> cooldowns;
        cooldowns.push_back(players[0]->getCooldown(Unit::Move::Basic));
        cooldowns.push_back(players[0]->getCooldown(Unit::Move::Wide));
        cooldowns.push_back(players[0]->getCooldown(Unit::Move::Offensive));
        cooldowns.push_back(players[0]->getCooldown(Unit::Move::Defensive));
        leftHotBar->setCooldowns(cooldowns);
        std::vector<const CircleHitbox*> circleHitboxes;
        for (auto& player : players) {
            circleHitboxes.push_back(player->getHitbox());
        }
        leftHotBar->checkCollision(circleHitboxes);
    }
    if (rightHotBar) {
        std::vector<float> cooldowns;
        cooldowns.push_back(players[1]->getCooldown(Unit::Move::Basic));
        cooldowns.push_back(players[1]->getCooldown(Unit::Move::Wide));
        cooldowns.push_back(players[1]->getCooldown(Unit::Move::Offensive));
        cooldowns.push_back(players[1]->getCooldown(Unit::Move::Defensive));
        rightHotBar->setCooldowns(cooldowns);
        std::vector<const CircleHitbox*> circleHitboxes;
        for (auto& player : players) {
            circleHitboxes.push_back(player->getHitbox());
        }
        rightHotBar->checkCollision(circleHitboxes);
    }
    leftHotBar->update(dt);
    rightHotBar->update(dt);
}

void World::init() {
    for (auto & player : players) {
        player->init();
    }
    for (auto & pattern : patterns) {
        pattern->init();
    }
    devTool = std::make_unique<DevTool>(this);
    leftHotBar = std::make_unique<SunPriestessHotBar>(true);
    rightHotBar = std::make_unique<SunPriestessHotBar>(false);
}

const Player* World::getPlayer(int playerId) const {
    for (const auto& player : players) {
        if (player->getPlayerId() == playerId) {
            return player.get();
        }
    }
    return nullptr;
}

std::vector<const Player*> World::getPlayers() const {
    std::vector<const Player*> playerPtrs;
    playerPtrs.reserve(players.size());

    for (const auto& player : players) {
        playerPtrs.push_back(player.get());
    }

    return playerPtrs;
}

std::vector<const Bullet*> World::getBullets() const {
    std::vector<const Bullet*> bulletPtrs;
    bulletPtrs.reserve(bullets.size());

    for (const auto& bullet : bullets) {
        bulletPtrs.push_back(bullet.get());
    }

    return bulletPtrs;
}

void World::addPlayer(std::unique_ptr<Player> player) {
    players.push_back(std::move(player));
}

void World::addPattern(std::unique_ptr<Pattern> pattern, float time) {
    pendingPatterns.emplace_back(std::move(pattern), time);
}

void World::spawnBullet(std::shared_ptr<Bullet> bullet) {
    pendingBullets.push_back(std::move(bullet));
}

void World::handlePendings(float dt) {
    while (!pendingBullets.empty()) {
        bullets.push_back(std::move(pendingBullets.back()));
        pendingBullets.pop_back();
    }
    for (auto it = pendingPatterns.begin(); it != pendingPatterns.end();) {
        if (it->second <= 0.0f) {
            patterns.push_back(std::move(it->first));
            it = pendingPatterns.erase(it);
        } else {
            it->second -= dt; // Decrease the time by a small value
            ++it;
        }
    }
}

void World::handleCollisions() {

    /* Bullet vs Bullet */ 
    std::vector<bool> toMakeDone(bullets.size(), false);
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (bullets[i]->isDone()) continue;
        const Hitbox* cleaner = bullets[i]->getCleansingHitbox();
        if (!cleaner) continue;

        for (size_t j = 0; j < bullets.size(); ++j) {
            if (bullets[j]->isWhose() == bullets[i]->isWhose() || bullets[j]->isDone() || toMakeDone[j]) continue;
            const Hitbox* body = bullets[j]->getLifeHitbox();
            if (body && cleaner->collidesWith(*body)) {
                toMakeDone[j] = true;
            }
        }
    }
    
    /* Bullet vs Player: Invincibility applying */
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (toMakeDone[i] || bullets[i]->isDone()) continue;
        for (const auto& [hb, major, who, duration] : bullets[i]->getInvincibilityHitboxes()) {
            if (!hb) continue;
            for (auto& player : players) {
                if (player->getPlayerId() == who && hb->collidesWith(*player->getHitbox())) {
                    player->applyInvincibility(duration, major);
                }
            }
        }
    }

    /* Bullet vs Player: Modifier applying */
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (toMakeDone[i] || bullets[i]->isDone()) continue;
        for (const auto& [hb, mod, who, duration, value] : bullets[i]->getModifierHitboxes()) {
            if (!hb) continue;
            for (auto& player : players) {
                if (player->getPlayerId() == who && player->getInvincibility(true) < Unit::EPS && hb->collidesWith(*player->getHitbox())) {
                    player->applyModifier(mod, duration, value);
                }
            }
        }
    }

    /* Bullet vs Player: Lock applying */
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (toMakeDone[i] || bullets[i]->isDone()) continue;
        for (const auto& [hb, lock, who, duration] : bullets[i]->getLockHitboxes()) {
            if (!hb) continue;
            for (auto& player : players) {
                if (player->getPlayerId() == who && player->getInvincibility(true) < Unit::EPS && hb->collidesWith(*player->getHitbox())) {
                    player->applyLock(lock, duration);
                }
            }
        }
    }

    /* Bullet vs Player: Damage applying */
    std::vector<int> hitPlayers;
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (toMakeDone[i] || bullets[i]->isDone()) continue;
        const Hitbox* dmg = bullets[i]->getDamagingHitbox();
        if (dmg) {
            for (auto& player : players) {
                if (std::find(hitPlayers.begin(), hitPlayers.end(), player->getPlayerId()) != hitPlayers.end()) continue;
                if (player->getInvincibility() < Unit::EPS 
                        && player->getPlayerId() != bullets[i]->isWhose() 
                        && dmg->collidesWith(*player->getHitbox())) {
                    hitPlayers.emplace_back(player->getPlayerId());
                    if (bullets[i]->getLifeHitbox()) {
                        toMakeDone[i] = true; 
                    }
                    break; 
                }
            }
        }
    }

    /* Apply damage to player */
    Unit::Vec2D hitLocation;
    float hitDuration = 1.0f;
    for (int hitPlayer : hitPlayers) {
        for (auto& player : players) {
            if (player->getPlayerId() == hitPlayer) {
                player->takeHit();
                hitLocation = player->getPosition();
                hitDuration = player->getLock(Unit::Lock::MovementLock);
                break;
            }
        }
    }

    /* Confirm hit to non-hit player */
    Unit::Vec2D hitterLocation = { Unit::BATTLEFIELD_WIDTH / 2, Unit::BATTLEFIELD_WIDTH / 2 };
    if (!hitPlayers.empty()) {
        for (auto& player : players) {
            if (std::find(hitPlayers.begin(), hitPlayers.end(), player->getPlayerId()) == hitPlayers.end()) {
                player->confirmHit();
                hitterLocation = player->getPosition();
            }
        }
    }
    
    /* send feedback */
   if (!hitPlayers.empty()){
        combatFeedbackManager.addHitText({hitLocation.x, hitLocation.y}, 
                                         {hitterLocation.x, hitterLocation.y}, 
                                          hitDuration);
        combatFeedbackManager.addHitEffect({hitLocation.x, hitLocation.y}, 
                                           {hitterLocation.x, hitterLocation.y});
        freezeTimer = freezeDuration = 0.5f;
   }

    /* Remove to-delete bullets */
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (toMakeDone[i]) {
            bullets[i]->makeDone();
        }
    }

    bullets.erase(
        std::remove_if(
            bullets.begin(),
            bullets.end(),
            [&](const std::shared_ptr<Bullet>& bullet) {
                return bullet->isDone();
            }
        ),
        bullets.end()
    );

}