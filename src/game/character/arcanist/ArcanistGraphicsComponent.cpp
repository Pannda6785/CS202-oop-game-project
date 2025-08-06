#include "ArcanistGraphicsComponent.hpp"
#include <raylib.h>
#include <string>
#include "../../../graphics/TextureManager.hpp"

ArcanistGraphicsComponent::ArcanistGraphicsComponent() : CharacterGraphicsComponent() {
    loadTextures();
}

ArcanistGraphicsComponent::~ArcanistGraphicsComponent() {
    unloadTextures();
}

void ArcanistGraphicsComponent::loadTextures() {
    auto loadAnim = [&](const std::string& basePath, int frameCount, int i0 = 0) -> std::vector<const Texture*> {
        std::vector<const Texture*> res;
        for (int i = i0; i < i0 + frameCount; ++i) {
            std::string path = basePath + std::to_string(i) + ".png";
            res.push_back(TextureManager::instance().getTexture(path));
        }
        return res;
    };

    std::string character_path = "../assets/sprites/arcanist/";
    animations["idle"] = Animation(loadAnim(character_path + "movement/idle", 2), 4, true);
    animations["walk"] = Animation(loadAnim(character_path + "movement/walk", 2), 8, true);
    animations["back"] = Animation(loadAnim(character_path + "movement/back", 2), 8, true);
}
