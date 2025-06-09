#include "World.h"

#include <algorithm>

#include <iostream>

void World::update(float dt) {
    // Update players
    for (auto& player : players) {
        player->update(dt);
    }

    // Update bullets
    for (auto& bullet : bullets) {
        bullet->update(dt);
    }

    // --- Build deletion mask ---
    std::vector<bool> toDelete(bullets.size(), false);

    // --- Bullet vs Bullet ---
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (bullets[i]->isDone()) continue;
        const Hitbox* cleaner = bullets[i]->getCleansingHitbox();
        if (!cleaner) continue;

        for (size_t j = 0; j < bullets.size(); ++j) {
            if (bullets[j]->isWhose() == bullets[i]->isWhose() || bullets[j]->isDone() || toDelete[j]) continue;
            const Hitbox* body = bullets[j]->getLifeHitbox();
            if (body && cleaner->collidesWith(*body)) {
                toDelete[j] = true;
            }
        }
    }

    // --- Bullet vs Player ---
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (bullets[i]->isDone() || toDelete[i]) continue;
        const Hitbox* dmg = bullets[i]->getDamagingHitbox();
        if (dmg) {
            for (auto& player : players) {
                if (player->getStatusEffects()[static_cast<int>(Unit::StatusEffect::Invincible)] < Unit::EPS 
                        && player->getId() != bullets[i]->isWhose() 
                        && dmg->collidesWith(*player->getHitbox())) {
                    player->registerHit();
                    toDelete[i] = true; // Mark bullet for deletion
                    break; // No need to check other players
                }
            }
        }

        for (const auto& [hb, effect, duration, targetId] : bullets[i]->getStatusEffectHitboxes()) {
            if (!hb) continue;
            for (auto& player : players) {
                if (player->getId() == targetId && hb->collidesWith(*player->getHitbox())) {
                    player->applyStatusEffect(effect, duration); // Apply for 1.0s
                }
            }
        }
    }

    // --- Remove marked bullets ---
    std::vector<std::unique_ptr<Bullet>> newBullets;
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (!toDelete[i] && !bullets[i]->isDone()) {
            newBullets.push_back(std::move(bullets[i]));
        }
    }

    if (players.size() >= 2) {
    const Hitbox* hitboxA = players[0]->getHitbox();
    const Hitbox* hitboxB = players[1]->getHitbox();

    if (hitboxA && hitboxB && hitboxA->collidesWith(*hitboxB)) {
        // Play default collision sound
        std::cout << "Collision detected between players!" << std::endl;
    }
}

    bullets = std::move(newBullets);
}


const Player* World::getPlayer(int playerId) const {
    for (const auto& player : players) {
        if (player->getId() == playerId) {
            return player.get();
        }
    }
    return nullptr; // Not found
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

void World::spawnBullet(std::unique_ptr<Bullet> bullet) {
    bullets.push_back(std::move(bullet));
}

