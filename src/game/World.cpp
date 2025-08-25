#include "World.hpp"

#include <algorithm>
#include <iostream>

#include "world_graphics/HUD/hot_bar/HotBarFactory.hpp"
#include "world_graphics/HUD/health_bar/HealthBarFactory.hpp"

World::World() : devTool(nullptr) {}

void World::update(float dt) {
    devTool->update(dt);
    dt *= devTool->getTimeScale();
    if (dt < Unit::EPS) return;
    
    camera->update(dt);
    hud->update(dt);
    if ((freezeTimer -= dt) > 0.0f) return;
    
    for (auto& player : players) player->update(dt);
    for (auto& pattern : patterns) pattern->update(dt);
    for (auto& bullet : bullets) bullet->update(dt);
    
    handlePendings(dt);
    handleCollisions();
    
    if ((resetRoundTimer -= dt) < 0.0f) {
        resetRound();
        resetRoundTimer = 1e9;
    }
    
    if ((endGameTimer -= dt) < 0.0f) {
        endGame();
        endGameTimer = 1e9;
    }
    
    ribbonManager->update(dt);
    combatFeedbackManager->update(dt);
    background->update(dt);
}

void World::init() {
    for (auto & player : players) {
        player->init();
    }
    for (auto & pattern : patterns) {
        pattern->init();
    }
    devTool = std::make_unique<DevTool>(this);
    camera = std::make_unique<WorldCamera>(this);

    pendingBullets.clear();
    background = std::make_unique<WorldBackground>();
    hud = std::make_unique<HUD>(this);
    combatFeedbackManager = std::make_unique<CombatFeedbackManager>();
    ribbonManager = std::make_unique<MovingTextTileManager>();
    
    freezeTimer = 0.0f;
    resetRoundTimer = 1.5f;
    endGameTimer = 1e9;
    gameEnded = false;
}

bool World::isGameEnded() const {
    return gameEnded;
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

void World::spawnBullet(std::shared_ptr<Bullet> bullet) {
    pendingBullets.push_back(std::move(bullet));
}

void World::addPattern(std::unique_ptr<Pattern> pattern, float time) {
    pendingPatterns.emplace_back(std::move(pattern), time);
}

void World::addChallenge(std::unique_ptr<Challenge> challenge, float time) {
    pendingChallenges.emplace_back(std::move(challenge), time);
}

std::string World::getFinalResults() const {
    std::string results = "";
    for (const auto& player : players) {
        if (player->getStock() > 0) {
            results += "PLAYER " + std::to_string(player->getPlayerId() + 1) + " WINS";
        }
    }
    return results;
}

void World::handlePendings(float dt) {
    while (!pendingBullets.empty()) {
        bullets.push_back(std::move(pendingBullets.back()));
        pendingBullets.pop_back();
    }
    for (auto it = pendingPatterns.begin(); it != pendingPatterns.end();) {
        if (it->second <= 0.0f) {
            it->first->init();
            patterns.push_back(std::move(it->first));
            it = pendingPatterns.erase(it);
        } else {
            it->second -= dt; // Decrease the time by a small value
            ++it;
        }
    }
    for (auto it = pendingChallenges.begin(); it != pendingChallenges.end();) {
        if (it->second <= 0.0f) {
            it->first->apply(this);
            it = pendingChallenges.erase(it);
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
    if (!hitPlayers.empty()) registerHit(hitPlayers);

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

void World::registerHit(const std::vector<int>& hitPlayers) {
    if (hitPlayers.empty()) return;

    camera->shake();

    /* Confirm hit to non-hit player */
    Unit::Vec2D hitterLocation = { Unit::BATTLEFIELD_WIDTH / 2, Unit::BATTLEFIELD_WIDTH / 2 };
    for (auto& player : players) {
        if (std::find(hitPlayers.begin(), hitPlayers.end(), player->getPlayerId()) == hitPlayers.end()) {
            player->confirmHit();
            hitterLocation = player->getPosition();
        }
    }
    
    /* Apply damage to player */
    for (int hitPlayer : hitPlayers) {
        for (auto& player : players) {
            if (player->getPlayerId() == hitPlayer) {
                player->takeHit();
                combatFeedbackManager->applyHit(player->getPosition(), hitterLocation, player->getHealth());
                if (player->getHealth() <= 0) {
                    if (player->getStock() == 0) {
                        endGameTimer = END_GAME_DELAY;
                    } else {
                        resetRoundTimer = RESET_ROUND_DELAY;
                    }
                }
                break;
            }
        }
    }

    freezeTimer = FREEZE_DURATION;
}

void World::resetRound() {
    for(auto &player : players){
        player->resetRound();
    }
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->makeDone();
    }
    pendingBullets.clear();

    ribbonManager->addReady(3.0f);
    ribbonManager->addCountdown(3.0f);
}

void World::endGame() {
    gameEnded = true;
    std::cout << "Yo yo yo! Game ended in a victory for Player(s?): ";
    for (const auto& player : players) {
        if (player->getStock() > 0) {
            std::cout << "Player " << player->getPlayerId() << " ";
        }
    }
    std::cout << std::endl;
}