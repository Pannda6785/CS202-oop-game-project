#include "World.hpp"

#include <algorithm>

void World::update(float dt) {
    for (auto& player : players) {
        player->update(dt);
    }
    for (auto& bullet : bullets) {
        bullet->update(dt);
    }
    handleCollisions();
}

void World::init() {
    for (auto & player : players) {
        player->init();
    }
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

void World::spawnBullet(std::unique_ptr<Bullet> bullet) {
    bullets.push_back(std::move(bullet));
}

void World::handleCollisions() {
    /* Clamp player positions to battlefield boundaries */  
    for (auto& player : players) {
        if (player->getPosition().x < 0 || player->getPosition().x > Unit::BATTLEFIELD_WIDTH ||
            player->getPosition().y < 0 || player->getPosition().y > Unit::BATTLEFIELD_HEIGHT) {
            player->setPosition({
                std::clamp(player->getPosition().x, 0.0f, Unit::BATTLEFIELD_WIDTH),
                std::clamp(player->getPosition().y, 0.0f, Unit::BATTLEFIELD_HEIGHT)
            });
        }
    }
    
    /* Bullet vs Bullet */ 
    std::vector<bool> toDelete(bullets.size(), false);
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
    
    /* Bullet vs Player: Invincibility applying */
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (toDelete[i] || bullets[i]->isDone()) continue;
        for (const auto& [hb, who, duration] : bullets[i]->getInvincibilityHitboxes()) {
            if (!hb) continue;
            for (auto& player : players) {
                if (player->getPlayerId() == who && hb->collidesWith(*player->getHitbox())) {
                    player->applyInvincibility(duration);
                }
            }
        }
    }

    /* Bullet vs Player: Damage applying */
    std::vector<int> hitPlayers;
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (toDelete[i] || bullets[i]->isDone()) continue;
        const Hitbox* dmg = bullets[i]->getDamagingHitbox();
        if (dmg) {
            for (auto& player : players) {
                if (std::find(hitPlayers.begin(), hitPlayers.end(), player->getPlayerId()) != hitPlayers.end()) continue;
                if (player->getInvincibility() < Unit::EPS 
                        && player->getPlayerId() != bullets[i]->isWhose() 
                        && dmg->collidesWith(*player->getHitbox())) {
                    hitPlayers.emplace_back(player->getPlayerId());
                    if (bullets[i]->getLifeHitbox()) {
                        toDelete[i] = true; 
                    }
                    break; 
                }
            }
        }
    }

    /* Apply damage to player */
    for (int hitPlayer : hitPlayers) {
        for (auto& player : players) {
            if (player->getPlayerId() == hitPlayer) {
                player->takeHit();
                break;
            }
        }
    }

    /* Confirm hit to non-hit player */
    if (!hitPlayers.empty()) {
        for (auto& player : players) {
            if (std::find(hitPlayers.begin(), hitPlayers.end(), player->getPlayerId()) == hitPlayers.end()) {
                player->confirmHit();
            }
        }
    }
    
    /* Remove to-delete bullets */
    std::vector<std::unique_ptr<Bullet>> newBullets;
    for (size_t i = 0; i < bullets.size(); ++i) {
        if (!toDelete[i] && !bullets[i]->isDone()) {
            newBullets.push_back(std::move(bullets[i]));
        }
    }
    bullets = std::move(newBullets);

}
