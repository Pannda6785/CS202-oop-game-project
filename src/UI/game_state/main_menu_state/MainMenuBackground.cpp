#include "MainMenuBackground.hpp"
#include <raylib.h>
#include "../../../Unit.hpp"

MainMenuBackground::MainMenuBackground() = default;

void MainMenuBackground::loadCharTexture(const std::string& texturePath) {
    charTexture = LoadTexture(texturePath.c_str());
    loadedChar = charTexture.id != 0;
    setLayer(10);
}

void MainMenuBackground::loadTitleTexture(const std::string& texturePath) {
    titleTexture = LoadTexture(texturePath.c_str());
    loadedTitle = titleTexture.id != 0;
    setLayer(10);
}

void MainMenuBackground::loadDecorationTexture(const std::string& texturePath) {
    decorationTexture = LoadTexture(texturePath.c_str());
    loadedDecoration = decorationTexture.id != 0;
    setLayer(10);
}

void MainMenuBackground::unloadTextures() {
    if (loadedChar) {
        UnloadTexture(charTexture);
        loadedChar = false;
    }
    if (loadedTitle) {
        UnloadTexture(titleTexture);
        loadedTitle = false;
    }
    if (loadedDecoration) {
        UnloadTexture(decorationTexture);
        loadedDecoration = false;
    }
}

MainMenuBackground::~MainMenuBackground() {
    unloadTextures();
}

void MainMenuBackground::render() const {
    if (loadedChar) {
        DrawTexture(charTexture, 900, 150, WHITE);
    }
    if (loadedTitle) {
        DrawTexture(titleTexture, 830, 350, WHITE);
    }
    if (loadedDecoration) {
        DrawTexture(decorationTexture, 900, 150, WHITE);
    }
}