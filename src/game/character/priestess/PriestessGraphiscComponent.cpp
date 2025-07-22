#include "PriestessGraphicsComponent.hpp"
#include <raylib.h>
#include <string>

#include "../../../graphics/TextureManager.hpp"

PriestessGraphicsComponent::PriestessGraphicsComponent() : CharacterGraphicsComponent() {
    loadTextures();
}

PriestessGraphicsComponent::~PriestessGraphicsComponent() {
    unloadTextures();
}

void PriestessGraphicsComponent::loadTextures() {
    auto loadAnim = [&](const std::string& basePath, int frameCount, int i0 = 0) -> std::vector<const Texture*> {
        std::vector<const Texture*> res;
        for (int i = i0; i < i0 + frameCount; ++i) {
            std::string path = basePath + std::to_string(i) + ".png";
            res.push_back(TextureManager::instance().getTexture(path));
        }
        return res;
    };

    std::string character_path = "../assets/sprites/priestess/";
    animations["idle"] = Animation(loadAnim(character_path + "movement/idle", 2), 4, true);
    animations["walk"] = Animation(loadAnim(character_path + "movement/walk", 2), 4, true);
    animations["back"] = Animation(loadAnim(character_path + "movement/back", 2), 4, true);

    animations["stagger"] = Animation(loadAnim(character_path + "hit/stagger", 2), 6, true);
    animations["wake"] = Animation(loadAnim(character_path + "hit/wake", 6), 6, false);

    animations["basic_start"] = Animation(loadAnim(character_path + "moveset/basic", 1), 8, false);
    animations["basic_loop"] = Animation(loadAnim(character_path + "moveset/basic", 2, 1), 6, true);
    animations["cast"] = Animation(loadAnim(character_path + "moveset/cast", 3), 8, true);
    animations["spin"] = Animation(loadAnim(character_path + "moveset/spin", 5), 10, false);
    animations["yell"] = Animation(loadAnim(character_path + "moveset/yell", 2), 8, true);
}

void PriestessGraphicsComponent::useBasic(float loopTime) {
    playAnim("basic_start", true);
    remainingBasicLoopTime = loopTime;
    remainingYellTime = 0.0f;
}

void PriestessGraphicsComponent::startCasting() {
    isCasting = true;
}

void PriestessGraphicsComponent::stopCasting() {
    isCasting = false;
}

void PriestessGraphicsComponent::spin() {
    playAnim("spin", true);
    remainingBasicLoopTime = 0.0f;
    remainingYellTime = 0.0f;
}

void PriestessGraphicsComponent::yell(float yellTime) {
    playAnim("yell", true);
    remainingYellTime = yellTime;
    remainingBasicLoopTime = 0.0f;
}

bool PriestessGraphicsComponent::characterSpecificUpdate(float dt) {
    remainingBasicLoopTime -= dt;
    remainingYellTime -= dt;

    if (currentAnimName == "spin" && !animFinished()) {
        playAnim("spin");
        return true;
    }
    if (currentAnimName == "spin" && animFinished()) {
        yell();
        return true;
    }
    if (currentAnimName == "yell" && remainingYellTime > Unit::EPS) {
        playAnim("yell");
        return true;
    } 
    if (currentAnimName == "basic_loop" && remainingBasicLoopTime > Unit::EPS) {
        playAnim("basic_loop");
        return true;
    }
    if (currentAnimName == "basic_start" && !animFinished()) {
        playAnim("basic_start");
        return true;
    }
    if (currentAnimName == "basic_start" && animFinished()) {
        playAnim("basic_loop");
        return true;
    }
    if (isCasting) {
        playAnim("cast");
        return true;
    }

    return false;
}