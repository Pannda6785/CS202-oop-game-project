#include "HeroGraphicsComponent.hpp"
#include <raylib.h>
#include <string>
#include "../../../graphics/TextureManager.hpp"

HeroGraphicsComponent::HeroGraphicsComponent() : CharacterGraphicsComponent() {
    signatureColor = {113, 255, 62, 255};
    loadTextures();
}

HeroGraphicsComponent::~HeroGraphicsComponent() {
    unloadTextures();
}

void HeroGraphicsComponent::loadTextures() {
    auto loadAnim = [&](const std::string& basePath, int frameCount, int i0 = 0) -> std::vector<const Texture*> {
        std::vector<const Texture*> res;
        for (int i = i0; i < i0 + frameCount; ++i) {
            std::string path = basePath + std::to_string(i) + ".png";
            res.push_back(TextureManager::instance().getTexture(path));
        }
        return res;
    };

    std::string character_path = "../assets/sprites/hero/";
    animations["idle"] = Animation(loadAnim(character_path + "movement/idle", 2), 4, true);
    animations["walk"] = Animation(loadAnim(character_path + "movement/walk", 2), 8, true);
    animations["back"] = Animation(loadAnim(character_path + "movement/back", 2), 8, true);

    animations["stagger"] = Animation(loadAnim(character_path + "hit/stagger", 2), 6, true);
    animations["wake"] = Animation(loadAnim(character_path + "hit/wake", 5), 5, false);

    animations["slash0"] = Animation(loadAnim(character_path + "moveset/slash0", 2), 8, false);
    animations["slash1"] = Animation(loadAnim(character_path + "moveset/slash1", 2), 12, false);
    animations["slash2"] = Animation(loadAnim(character_path + "moveset/slash2", 3), 10, false);
    animations["slash3"] = Animation(loadAnim(character_path + "moveset/slash3", 1), 8, false);
    animations["roll"] = Animation(loadAnim(character_path + "moveset/roll", 5), 10, false);
    animations["stun"] = Animation(loadAnim(character_path + "moveset/stun", 5), 8, false);
}

void HeroGraphicsComponent::useBasic(int step) {
    if (step == 0) {
        slashBuffer.clear();
    }
    if (step == 0) slashBuffer.push_back("slash0");
    else if (step == 1) slashBuffer.push_back("slash1"), slashBuffer.push_back("slash2");
    else if (step == 2) slashBuffer.push_back("slash3");
    if (currentAnimName.rfind("slash", 0) != 0) {
        playAnim(slashBuffer.front(), true);
        slashBuffer.pop_front();
    }
}

void HeroGraphicsComponent::useWide() {
    slashBuffer.clear();
    for (int i = 0; i < 3; i++) {
        slashBuffer.push_back("slash2");
    }
    if (currentAnimName.rfind("slash", 0) != 0) {
        playAnim(slashBuffer.front(), true);
        slashBuffer.pop_front();
    }
}

void HeroGraphicsComponent::roll() {
    slashBuffer.clear();
    playAnim("roll", true);
}

void HeroGraphicsComponent::stun() {
    slashBuffer.clear();
    playAnim("stun", true);
}

bool HeroGraphicsComponent::characterSpecificUpdate(float dt) {
    if (currentAnimName == "roll" && !animFinished()) {
        playAnim("roll");
        return true;
    }
    if (currentAnimName == "stun" && !animFinished()) {
        playAnim("stun");
        return true;
    }
    if (currentAnimName.rfind("slash", 0) == 0 && !animFinished()) {
        playAnim(currentAnimName);
        return true;
    }
    if (currentAnimName.rfind("slash", 0) == 0 && animFinished() && !slashBuffer.empty()) {
        playAnim(slashBuffer.front(), true);
        slashBuffer.pop_front();
        return true;
    }
    slashBuffer.clear();
    return false;
}
