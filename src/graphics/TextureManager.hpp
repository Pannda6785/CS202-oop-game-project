#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "raylib.h"
#include <string>
#include <unordered_map>

class TextureManager {
public:
    static TextureManager& instance();

    void preloadTextures();
    const Texture* getTexture(std::string path);
    void clear();

private:
    TextureManager() = default;
    ~TextureManager();

    // Delete copy/move
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    void loadTexture(const std::string& path);

    std::unordered_map<std::string, Texture> textureCache;
};

#endif // TEXTURE_MANAGER_HPP
