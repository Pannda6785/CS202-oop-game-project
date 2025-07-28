#include "Artwork.hpp"
#include <raylib.h>
#include <iostream>

Artwork::Artwork(float period)
    : period(period) {
    
}

Artwork::~Artwork() = default;

void Artwork::unloadTextures() {
    for (auto& tex : textures) {
        if (tex.id != 0) {
            UnloadTexture(tex);
        }
    }
    textures.clear();
    texturePaths.clear();
}

bool Artwork::addTexture(const std::string& filePath) {
    Texture2D tex = LoadTexture(filePath.c_str());
    if (tex.id != 0) {
        textures.push_back(tex);
        texturePaths.push_back(filePath);
        return true;
    } else {
        std::cerr << "Failed to load artwork texture: " << filePath << std::endl;
        return false;
    }
}

void Artwork::setPosition(int x, int y) {
    posX = x;
    posY = y;
}

void Artwork::setSize(int width, int height) {
    drawWidth = width;
    drawHeight = height;
}

void Artwork::setPeriod(float p) {
    period = p;
}

void Artwork::setScale(float s) {
    scale = s;
}

int Artwork::getWidth() const {
    if (textures.empty()) return 0;
    return drawWidth > 0 ? drawWidth : textures[0].width;
}

void Artwork::render() const {
    if (textures.empty()) return;
    float time = GetTime();
    const Texture2D& tex = textures[static_cast<int>(time / period) % textures.size()];
    int w = drawWidth > 0 ? drawWidth : tex.width;
    int h = drawHeight > 0 ? drawHeight : tex.height;

    // DrawTextureEx(tex, {(float)posX, (float)posY}, 0.0f, (float)w / tex.width, WHITE);

    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest = { posX, posY, tex.width * scale, tex.height * scale };
    Vector2 origin = { 0, 0 }; // Không xoay
    float rotation = 0;
    
    DrawTexturePro(tex, source, dest, origin, rotation, WHITE);
}