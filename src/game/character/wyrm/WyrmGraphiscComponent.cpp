#include "WyrmGraphicsComponent.hpp"
#include <raylib.h>
#include <string>
#include "../../../graphics/TextureManager.hpp"

WyrmGraphicsComponent::WyrmGraphicsComponent() : CharacterGraphicsComponent() {
    signatureColor = {255, 234, 155, 255};
    loadTextures();
}

WyrmGraphicsComponent::~WyrmGraphicsComponent() {
    unloadTextures();
}

void WyrmGraphicsComponent::loadTextures() {
    transform();
    detransform();
}

void WyrmGraphicsComponent::transform() {
    signatureColor = {118, 11, 186, 240};
    _loadTextures("../assets/sprites/wyrm/dreadwyrm/");
}

void WyrmGraphicsComponent::detransform() {
    signatureColor = {255, 234, 155, 255}; 
    _loadTextures("../assets/sprites/wyrm/");
}

void WyrmGraphicsComponent::_loadTextures(std::string character_path) { // for eample: character_path = "../assets/sprites/wyrm/"
    auto loadAnim = [&](const std::string& basePath, int frameCount, int i0 = 0) -> std::vector<const Texture*> {
        std::vector<const Texture*> res;
        for (int i = i0; i < i0 + frameCount; ++i) {
            std::string path = basePath + std::to_string(i) + ".png";
            res.push_back(TextureManager::instance().getTexture(path));
        }
        return res;
    };

    animations["idle"] = Animation(loadAnim(character_path + "movement/idle", 2), 4, true);
    animations["walk"] = Animation(loadAnim(character_path + "movement/walk", 2), 8, true);
    animations["back"] = Animation(loadAnim(character_path + "movement/back", 2), 8, true);

    animations["stagger"] = Animation(loadAnim(character_path + "hit/stagger", 2), 6, true);
    animations["wake"] = Animation(loadAnim(character_path + "hit/wake", 6), 6, false);

    animations["command_start"] = Animation(loadAnim(character_path + "moveset/command", 1), 8, true);
    animations["command_loop"] = Animation(loadAnim(character_path + "moveset/command", 2, 1), 8, true);

    animations["blast_start"] = Animation(loadAnim(character_path + "moveset/blast", 1), 1, true);
    animations["blast_loop"] = Animation(loadAnim(character_path + "moveset/blast", 2, 1), 8, true);

    animations["roar_start"] = Animation(loadAnim(character_path + "moveset/roar", 1), 1, true);
    animations["roar_loop"] = Animation(loadAnim(character_path + "moveset/roar", 2, 1), 8, true);
}

void WyrmGraphicsComponent::command(float chargeDuration, float loopDuration) {
    playAnim("command_start", true);
    remainingCommandCharge = chargeDuration;
    remainingCommandLoop = loopDuration;
}

void WyrmGraphicsComponent::blast(float chargeDuration, float loopDuration) {
    playAnim("blast_start", true);
    remainingBlastCharge = chargeDuration;
    remainingBlastLoop = loopDuration;
}

void WyrmGraphicsComponent::roar(float chargeDuration, float loopDuration) {
    playAnim("roar_start", true);
    remainingRoarCharge = chargeDuration;
    remainingRoarLoop = loopDuration;
}


bool WyrmGraphicsComponent::characterSpecificUpdate(float dt) {
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

    if (work("command_start", "command_loop", remainingCommandCharge, remainingCommandLoop)) return true;
    if (work("blast_start", "blast_loop", remainingBlastCharge, remainingBlastLoop)) return true;
    if (work("roar_start", "roar_loop", remainingRoarCharge, remainingRoarLoop)) return true;

    return false;
}

