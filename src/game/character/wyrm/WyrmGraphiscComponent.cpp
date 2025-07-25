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
    animations["roar_charge"] = Animation(loadAnim(character_path + "moveset/roar_charge", 1), 1, true);
    animations["roar"] = Animation(loadAnim(character_path + "moveset/roar", 2), 8, true);
    animations["offensive_charge"] = Animation(loadAnim(character_path + "moveset/offensive_charge", 1), 1, true);
    animations["offensive"] = Animation(loadAnim(character_path + "moveset/offensive", 2), 8, true);
}

void WyrmGraphicsComponent::useBasic() {
    playAnim("basic", true);
}

void WyrmGraphicsComponent::useOffensive(bool firstUse, float chargeDuration, float offensiveDuration) {
    if (firstUse || offensiveDuration <= Unit::EPS) {
        playAnim("offensive_charge", true);
        remainingOffensiveChargeTime = chargeDuration;
        remainingOffensiveTime = offensiveDuration;
        remainingRoarChargeTime = 0.0f;
        remainingRoarTime = 0.0f;
        return;
    }
    if (remainingOffensiveChargeTime > Unit::EPS) {
        remainingOffensiveTime = chargeDuration + offensiveDuration - remainingOffensiveChargeTime;
    } else {
        remainingOffensiveTime = chargeDuration + offensiveDuration;
    }
}

void WyrmGraphicsComponent::roar(float chargeDuration, float roarDuration) {
    playAnim("roar_charge", true);
    remainingRoarChargeTime = chargeDuration;
    remainingRoarTime = roarDuration;
    remainingOffensiveChargeTime = 0.0f;
    remainingOffensiveTime = 0.0f;
}

bool WyrmGraphicsComponent::characterSpecificUpdate(float dt) {
    if (currentAnimName == "roar_charge" && remainingRoarChargeTime > Unit::EPS) {
        remainingRoarChargeTime -= dt;
        playAnim("roar_charge");
        return true;
    }
    if (currentAnimName == "roar_charge") {
        playAnim("roar", true);
    }
    if (currentAnimName == "roar" && remainingRoarTime > Unit::EPS) {
        remainingRoarTime -= dt;
        playAnim("roar");
        return true;
    }

    if (currentAnimName == "offensive_charge" && remainingOffensiveChargeTime > Unit::EPS) {
        remainingOffensiveChargeTime -= dt;
        playAnim("offensive_charge");
        return true;
    }
    if (currentAnimName == "offensive_charge") {
        playAnim("offensive", true);
    }
    if (currentAnimName == "offensive" && remainingOffensiveTime > Unit::EPS) {
        remainingOffensiveTime -= dt;
        playAnim("offensive");
        return true;
    }

    if (currentAnimName == "basic" && !animFinished()) {
        playAnim("basic");
        return true;
    }

    return false;
}