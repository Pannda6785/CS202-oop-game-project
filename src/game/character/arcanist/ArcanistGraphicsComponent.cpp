#include "ArcanistGraphicsComponent.hpp"
#include <raylib.h>
#include <string>
#include "../../../graphics/TextureManager.hpp"

ArcanistGraphicsComponent::ArcanistGraphicsComponent() : CharacterGraphicsComponent() {
    signatureColor = {222, 222, 222, 255};
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

    
    animations["stagger"] = Animation(loadAnim(character_path + "hit/stagger", 2), 6, true);
    animations["wake"] = Animation(loadAnim(character_path + "hit/wake", 6), 6, false);

    animations["smug_start"] = Animation(loadAnim(character_path + "moveset/smug", 1), 1, true);
    animations["smug_loop"] = Animation(loadAnim(character_path + "moveset/smug", 2, 1), 8, true);
}

void ArcanistGraphicsComponent::useOffensive() {
    playAnim("smug_start", true);
    remainingSmugCharge = 0.1f;
    remainingSmugLoop = 0.4f;
}

bool ArcanistGraphicsComponent::characterSpecificUpdate(float dt) {
    auto work = [&](std::string start, std::string loop, float &remCharge, float &remLoop) -> bool{
        if (currentAnimName == start && remCharge > Unit::EPS) {
            remCharge -= dt;
            playAnim(start);
            return true;
        }
        if (currentAnimName == start) {
            playAnim(loop, true);
        }
        if (currentAnimName == loop && remLoop > Unit::EPS) {
            remLoop -= dt;
            playAnim(loop);
            return true;
        }
        return false;
    };

    if (work("smug_start", "smug_loop", remainingSmugCharge, remainingSmugLoop)) return true;

    return false;
}

