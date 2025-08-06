#include "LichGraphicsComponent.hpp"
#include <raylib.h>
#include <string>
#include "../../../graphics/TextureManager.hpp"

LichGraphicsComponent::LichGraphicsComponent() : CharacterGraphicsComponent() {
    signatureColor = {51, 79, 255, 255};
    loadTextures();
}

LichGraphicsComponent::~LichGraphicsComponent() {
    unloadTextures();
}

void LichGraphicsComponent::loadTextures() {
    auto loadAnim = [&](const std::string& basePath, int frameCount, int i0 = 0) -> std::vector<const Texture*> {
        std::vector<const Texture*> res;
        for (int i = i0; i < i0 + frameCount; ++i) {
            std::string path = basePath + std::to_string(i) + ".png";
            res.push_back(TextureManager::instance().getTexture(path));
        }
        return res;
    };

    std::string character_path = "../assets/sprites/lich/";
    animations["idle"] = Animation(loadAnim(character_path + "movement/idle", 2), 4, true);
    animations["walk"] = Animation(loadAnim(character_path + "movement/walk", 2), 8, true);
    animations["back"] = Animation(loadAnim(character_path + "movement/back", 2), 8, true);

    animations["stagger"] = Animation(loadAnim(character_path + "hit/stagger", 3), 6, true);
    animations["wake"] = Animation(loadAnim(character_path + "hit/wake", 6), 6, false);

    animations["command_start"] = Animation(loadAnim(character_path + "moveset/command", 1), 8, true);
    animations["command_loop"] = Animation(loadAnim(character_path + "moveset/command", 2, 1), 8, true);

    animations["offensive_start"] = Animation(loadAnim(character_path + "moveset/offensive", 1), 8, true);
    animations["offensive_loop"] = Animation(loadAnim(character_path + "moveset/offensive", 2, 1), 8, true);

    animations["whisper_start"] = Animation(loadAnim(character_path + "moveset/whisper", 1), 8, true);
    animations["whisper_loop"] = Animation(loadAnim(character_path + "moveset/whisper", 2, 1), 8, true);
}

void LichGraphicsComponent::useBasic() {
    playAnim("command_start", true);
    remainingCommandCharge = 0.1f;
    remainingCommandLoop = 0.250f;
}

void LichGraphicsComponent::useWide() {
    if (currentAnimName == "whisper_loop") {
        remainingWhisperLoop = 0.625f;
        return;
    }
    playAnim("whisper_start", true);
    remainingWhisperCharge = 0.1f;
    remainingWhisperLoop = 0.625f;
}

void LichGraphicsComponent::useOffensive() {
    playAnim("offensive_start", true);
    remainingOffensiveCharge = 0.250f;
    remainingOffensiveLoop = 0.5f;
}

void LichGraphicsComponent::startCastingDefensive() {
    playAnim("whisper_loop", true);
    remainingWhisperLoop = 1e9;
}

void LichGraphicsComponent::endCastingDefensive(float startup) {
    playAnim("command_start", true);
    remainingCommandCharge = startup;
    remainingCommandLoop = 0.375f;
}

bool LichGraphicsComponent::characterSpecificUpdate(float dt) {

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
    if (work("whisper_start", "whisper_loop", remainingWhisperCharge, remainingWhisperLoop)) return true;
    if (work("offensive_start", "offensive_loop", remainingOffensiveCharge, remainingOffensiveLoop)) return true;

    return false;
}

