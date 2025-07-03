#include "PriestessGraphicsComponent.hpp"
#include <raylib.h>
#include <string>

PriestessGraphicsComponent::PriestessGraphicsComponent() : CharacterGraphicsComponent() {
    loadTextures();
}

PriestessGraphicsComponent::~PriestessGraphicsComponent() {
    unloadTextures();
}

void PriestessGraphicsComponent::loadTextures() {
    std::string character_path = "../assets/sprites/priestess/";

    for (int i = 0; i <= 1; ++i) {
        std::string path = character_path + "movement/idle" + std::to_string(i) + ".png";
        idleAnim.push_back(new Texture2D(LoadTexture(path.c_str())));
    }

    for (int i = 0; i <= 1; ++i) {
        std::string path = character_path + "movement/walk" + std::to_string(i) + ".png";
        walkAnim.push_back(new Texture2D(LoadTexture(path.c_str())));
    }

    for (int i = 0; i <= 1; ++i) {
        std::string path = character_path + "movement/back" + std::to_string(i) + ".png";
        backAnim.push_back(new Texture2D(LoadTexture(path.c_str())));
    }

    for (int i = 0; i <= 1; ++i) {
        std::string path = character_path + "hit/stagger" + std::to_string(i) + ".png";
        staggerAnim.push_back(new Texture2D(LoadTexture(path.c_str())));
    }

    for (int i = 0; i <= 5; ++i) {
        std::string path = character_path + "hit/wake" + std::to_string(i) + ".png";
        wakeAnim.push_back(new Texture2D(LoadTexture(path.c_str())));
    }

    // TO DO: If you later decide to use actual textures instead of debug drawing:
    // hitboxTexture = new Texture2D(LoadTexture("../assets/sprites/hitbox.png"));
    // arrowTexture = new Texture2D(LoadTexture("../assets/sprites/arrow.png"));
}

void PriestessGraphicsComponent::unloadTextures() {
    auto unload = [](std::vector<Texture2D*>& animVec) {
        for (Texture2D* tex : animVec) {
            if (tex) {
                UnloadTexture(*tex);  // unload actual texture
                delete tex;           // free memory
            }
        }
        animVec.clear();  // ensure vector is empty
    };

    unload(idleAnim);
    unload(walkAnim);
    unload(backAnim);
    unload(staggerAnim);
    unload(wakeAnim);

    // If you add these later, also do:
    // if (hitboxTexture) {
    //     UnloadTexture(*hitboxTexture);
    //     delete hitboxTexture;
    //     hitboxTexture = nullptr;
    // }

    // if (arrowTexture) {
    //     UnloadTexture(*arrowTexture);
    //     delete arrowTexture;
    //     arrowTexture = nullptr;
    // }
}
