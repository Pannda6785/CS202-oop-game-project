#include "TextureManager.hpp"

TextureManager& TextureManager::instance() {
    static TextureManager instance;
    return instance;
}

const Texture* TextureManager::getTexture(std::string path) {
    auto it = textureCache.find(path);
    if (it != textureCache.end()) {
        return &it->second;
    }
    Texture texture = LoadTexture(path.c_str());
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
