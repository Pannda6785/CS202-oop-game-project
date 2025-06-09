#include "Renderer.h"
#include "Player.h"

void Renderer::renderBattle() {
    auto players = world->getPlayers();
    for (auto& player : players) {
        player->render(*this);
    }
}

void Renderer::renderHUD() {
    // Empty as requested
}
