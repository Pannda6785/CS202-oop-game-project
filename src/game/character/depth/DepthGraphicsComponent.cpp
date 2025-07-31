#include "DepthGraphicsComponent.hpp"
#include <raylib.h>
#include <string>
#include "../../../graphics/TextureManager.hpp"

DepthGraphicsComponent::DepthGraphicsComponent() : CharacterGraphicsComponent() {
    loadTextures();
}

DepthGraphicsComponent::~DepthGraphicsComponent() {
    unloadTextures();
}

void DepthGraphicsComponent::loadTextures() {
    auto loadAnim = [&](const std::string& basePath, int frameCount, int i0 = 0) -> std::vector<const Texture*> {
        std::vector<const Texture*> res;
        for (int i = i0; i < i0 + frameCount; ++i) {
            std::string path = basePath + std::to_string(i) + ".png";
            res.push_back(TextureManager::instance().getTexture(path));
        }
        return res;
    };

    std::string character_path = "../assets/sprites/depth/";
    animations["idle"] = Animation(loadAnim(character_path + "movement/idle", 2), 4, true);
    animations["walk"] = Animation(loadAnim(character_path + "movement/walk", 2), 8, true);
    animations["back"] = Animation(loadAnim(character_path + "movement/back", 2), 8, true);

    animations["stagger"] = Animation(loadAnim(character_path + "hit/stagger", 2), 6, true);
    animations["wake"] = Animation(loadAnim(character_path + "hit/wake", 5), 5, false);

    animations["basic_start"] = Animation(loadAnim(character_path + "moveset/basic", 2), 3, false);
    animations["basic_loop"] = Animation(loadAnim(character_path + "moveset/basic", 2, 2), 8, true);
    animations["wide_start"] = Animation(loadAnim(character_path + "moveset/wide", 1), 8, false);
    animations["wide_loop"] = Animation(loadAnim(character_path + "moveset/wide", 2, 1), 8, true);
    animations["offensive"] = Animation(loadAnim(character_path + "moveset/offensive", 7), 10, false);
    animations["defensive_start"] = Animation(loadAnim(character_path + "moveset/defensive", 1), 8, false);
    animations["defensive_loop"] = Animation(loadAnim(character_path + "moveset/defensive", 2, 1), 8, true);
}

void DepthGraphicsComponent::useBasic(float loopTime) {
    playAnim("basic_start", true);
    remainingLoopTime = loopTime;
    isBasic = true;
    isWide = false;
    isDefensive = false;
}

void DepthGraphicsComponent::useWide(float loopTime) {
    playAnim("wide_start", true);
    remainingLoopTime = loopTime;
    isWide = true;
    isBasic = false;
    isDefensive = false;
}

void DepthGraphicsComponent::useOffensive() {
    playAnim("offensive", true);
    isBasic = false;
    isWide = false;
    isDefensive = false;
}

void DepthGraphicsComponent::useDefensive(float loopTime) {
    playAnim("defensive_start", true);
    remainingLoopTime = loopTime;
    isDefensive = true;
    isBasic = false;
    isWide = false;
}

bool DepthGraphicsComponent::characterSpecificUpdate(float dt) {
    remainingLoopTime -= dt;

    auto work = [&](std::string start, std::string loop) -> bool {
        if (currentAnimName == loop && remainingLoopTime > Unit::EPS) {
            playAnim(loop);
            return true;
        }
        if (currentAnimName == start && !animFinished()) {
            playAnim(start);
            return true;
        }
        if (currentAnimName == start && animFinished()) {
            playAnim(loop);
            return true;
        }
        return false;
    };

    if (isBasic && work("basic_start", "basic_loop")) return true;
    isBasic = false;
    if (isWide && work("wide_start", "wide_loop")) return true;
    isWide = false;
    if (isDefensive && work("defensive_start", "defensive_loop")) return true;
    isDefensive = false;
    if (currentAnimName == "offensive" && !animFinished()) {
        playAnim("offensive");
        return true;
    }
    return false;
}
