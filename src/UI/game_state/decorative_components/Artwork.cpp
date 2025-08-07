#include "Artwork.hpp"
#include "../../../graphics/TextureManager.hpp"
#include <raylib.h>
#include <iostream>
#include <cassert>

Artwork::Artwork() : GraphicsComponent(), period(1.0f), posX(0), posY(0), drawWidth(0), drawHeight(0), scale(1.0f), fadeInTime(0.0f), fadeInTimer(0.0f), middle(false), flip(false) {
}

Artwork::~Artwork(){
    unloadTextures();
}

void Artwork::unloadTextures() {
}

bool Artwork::addTexture(const std::string& filePath) {
    const Texture2D* tex = TextureManager::instance().getTexture(filePath);
    if (tex != nullptr && tex->id != 0) {
        textures.push_back(tex);
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
    if (textures.empty() || textures[0] == nullptr) return 0;
    return textures[0]->width * scale;
}

void Artwork::setFadeInTime(float time) {
    fadeInTime = time;
    fadeInTimer = 0.0f;
}

bool Artwork::finishedFadeIn() const {
    assert(fadeInTime >= 0.0f);
    return fadeInTimer >= fadeInTime;
}

void Artwork::setMiddle(bool mid) {
    middle = mid;
}

void Artwork::setFlip(bool flip) {
    this->flip = flip;
}

float Artwork::getFadeInTime() const {
    return fadeInTime;
}

float Artwork::getFadeInTimer() const {
    return fadeInTimer;
}

void Artwork::update(float dt) {
    timer += dt;
    if (fadeInTime > 0.0f) {
        fadeInTimer += dt;
        // std::cout << "adding " << dt << ' ' << fadeInTimer << std::endl;
        if (fadeInTimer > fadeInTime) {
            fadeInTimer = fadeInTime;
        }
    }
}

void Artwork::render() const {
    if (textures.empty() || textures[0] == nullptr) return;
    const Texture2D* tex = textures[static_cast<int>(timer / period) % textures.size()];
    tmp = static_cast<int>(timer / period) % textures.size();
    if(tmp != preTmp) std::cout << "tmp: " << tmp << std::endl;
    preTmp = tmp;
    int w = drawWidth > 0 ? drawWidth : tex->width;
    int h = drawHeight > 0 ? drawHeight : tex->height;
    Vector2 origin = {0.0f, 0.0f};
    Rectangle source = { 0, 0, (float)tex->width, (float)tex->height };
    Rectangle dest = { posX, posY, tex->width * scale, tex->height * scale };
    float rotation = 0;
    Color color = { 255, 255, 255, 255 * (fadeInTime > 0.0f ? fadeInTimer / fadeInTime : 1.0f) };
    if(fadeInTime > 0.0f) {
        // std::cout << "Fade in timer: " << fadeInTimer << " seconds" << std::endl;
        // std::cout << "Fade in time: " << fadeInTime << " seconds" << std::endl;
    }
    if(flip) source.width = -source.width;
    DrawTexturePro(*tex, source, dest, origin, rotation, color);
}