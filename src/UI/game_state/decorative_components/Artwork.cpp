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

void Artwork::setFadeInTime(float time) {
    fadeInTime = time;
}

void Artwork::update(float dt) {
    if (fadeInTime > 0.0f) {
        fadeInTimer += dt;
        if (fadeInTimer > fadeInTime) {
            fadeInTimer = fadeInTime; // Clamp to fade-in time
        }
    }
}

void Artwork::render() const {
    if (textures.empty()) return;
    float time = GetTime();
    const Texture2D& tex = textures[static_cast<int>(time / period) % textures.size()];
    int w = drawWidth > 0 ? drawWidth : tex.width;
    int h = drawHeight > 0 ? drawHeight : tex.height;

    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };
    Rectangle dest = { posX, posY, tex.width * scale, tex.height * scale };
    Vector2 origin = { 0, 0 };
    float rotation = 0;
    Color color = { 255, 255, 255, 255 * (fadeInTime > 0.0f ? fadeInTimer / fadeInTime : 1.0f) };
    DrawTexturePro(tex, source, dest, origin, rotation, color);
}