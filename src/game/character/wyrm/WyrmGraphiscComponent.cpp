#include "WyrmGraphicsComponent.hpp"
#include <raylib.h>
#include <string>

#include "../../../graphics/TextureManager.hpp"

WyrmGraphicsComponent::WyrmGraphicsComponent() : CharacterGraphicsComponent() {
    loadTextures();
}

WyrmGraphicsComponent::~WyrmGraphicsComponent() {
    unloadTextures();
}

void WyrmGraphicsComponent::loadTextures() {
    auto loadAnim = [&](const std::string& basePath, int frameCount, int i0 = 0) -> std::vector<const Texture*> {
        std::vector<const Texture*> res;
        for (int i = i0; i < i0 + frameCount; ++i) {
            std::string path = basePath + std::to_string(i) + ".png";
            res.push_back(TextureManager::instance().getTexture(path));
        }
        return res;
    };

    std::string character_path = "../assets/sprites/wyrm/";
    animations["idle"] = Animation(loadAnim(character_path + "movement/idle", 2), 4, true);
    animations["walk"] = Animation(loadAnim(character_path + "movement/walk", 2), 8, true);
    animations["back"] = Animation(loadAnim(character_path + "movement/back", 2), 8, true);

    animations["stagger"] = Animation(loadAnim(character_path + "hit/stagger", 2), 6, true);
    animations["wake"] = Animation(loadAnim(character_path + "hit/wake", 6), 6, false);

    animations["basic"] = Animation(loadAnim(character_path + "moveset/basic", 3), 8, false);
    animations["offensive_charge"] = Animation(loadAnim(character_path + "moveset/offensive_charge", 1), 1, true);
    animations["offensive"] = Animation(loadAnim(character_path + "moveset/offensive", 2), 8, true);
    animations["roar_charge"] = Animation(loadAnim(character_path + "moveset/roar_charge", 1), 1, true);
    animations["roar"] = Animation(loadAnim(character_path + "moveset/roar", 2), 8, true);
}

void WyrmGraphicsComponent::useBasic() {
    playAnim("basic", true);
}

bool WyrmGraphicsComponent::characterSpecificUpdate(float dt) {
    if (currentAnimName == "basic" && !animFinished()) {
        playAnim("basic");
        return true;
    }
    return false;
}