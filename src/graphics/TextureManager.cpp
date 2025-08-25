#include "TextureManager.hpp"

#include <iostream>

TextureManager& TextureManager::instance() {
    static TextureManager instance;
    return instance;
}

void TextureManager::preloadTextures() {
    loadTexture("../assets/textures/character_spritesheet.png");
}

const Texture* TextureManager::getTexture(std::string path) {
    auto it = textureCache.find(path);
    if (it != textureCache.end()) {
        return &it->second;
    }
    Texture texture = LoadTexture(path.c_str());
    if (texture.id == 0) {
        std::cerr << "Warning: TextureManager - Failed to load texture: " << path << std::endl;
        return nullptr;
    }
    textureCache[path] = texture;
    return &textureCache[path];
}

void TextureManager::clear() {
    for (auto& pair : textureCache) {
        UnloadTexture(pair.second);
    }
    textureCache.clear();
}

TextureManager::~TextureManager() {
    clear();
}

void TextureManager::loadTexture(const std::string& path) {
    Texture texture = LoadTexture(path.c_str());
    if (texture.id == 0) {
        std::cerr << "Warning: TextureManager - Failed to load texture: " << path << std::endl;
        return;
    }
    textureCache[path] = texture;
}
