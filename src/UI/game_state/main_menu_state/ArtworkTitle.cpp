#include "ArtworkTitle.hpp"
#include <raylib.h>
#include "../../../Unit.hpp"

ArtworkTitle::ArtworkTitle() = default;

void ArtworkTitle::loadCharTexture(const std::string& texturePath) {
    charTexture = LoadTexture(texturePath.c_str());
    loadedChar = charTexture.id != 0;
    setLayer(10);
}

void ArtworkTitle::loadTitleTexture(const std::string& texturePath) {
    titleTexture = LoadTexture(texturePath.c_str());
    loadedTitle = titleTexture.id != 0;
    setLayer(10);
}

void ArtworkTitle::loadDecorationTexture(const std::string& texturePath) {
    decorationTexture = LoadTexture(texturePath.c_str());
    loadedDecoration = decorationTexture.id != 0;
    setLayer(10);
}

void ArtworkTitle::unloadTextures() {
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

ArtworkTitle::~ArtworkTitle() {
}

void ArtworkTitle::render() const {
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