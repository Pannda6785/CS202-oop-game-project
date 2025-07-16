#include "MainMenuBackground.hpp"
#include <raylib.h>
#include "../../../Unit.hpp"

MainMenuBackground::MainMenuBackground() = default;

void MainMenuBackground::loadTexture(const std::string& texturePath) {
    backgroundTexture = LoadTexture(texturePath.c_str());
    loaded = backgroundTexture.id != 0;
    setLayer(0);
}

MainMenuBackground::~MainMenuBackground() {
    if (loaded) {
        UnloadTexture(backgroundTexture);
    }
}

void MainMenuBackground::render() const {
    if (loaded) {
        DrawTexture(backgroundTexture, 0, 0, WHITE);
    } else{
        // Fallback rendering if texture failed to load
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), DARKGRAY);
    }
}