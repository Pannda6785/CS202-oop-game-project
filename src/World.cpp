#include "World.h"

void World::update(float dt) {
    for (auto& player : players) {
        player.update(dt);
    }
    // TO DO
    // update bullet
    // handle collisions
}

std::vector<const Player*> World::getPlayers() const {
    std::vector<const Player*> playerPtrs;
    playerPtrs.reserve(players.size());

    for (const auto& player : players) {
        playerPtrs.push_back(&player);
    }

    return playerPtrs;
}

const Player* World::getPlayer(int playerId) const {
    for (const auto& player : players) {
        if (player.getId() == playerId) {
            return &player;
        }
    }
    return nullptr; // Return nullptr if not found
}

void World::addPlayer(Player player) {
    players.push_back(std::move(player));
}
