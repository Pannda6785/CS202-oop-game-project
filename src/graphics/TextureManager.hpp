#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "raylib.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>

class TextureManager {
public:
    static TextureManager& instance();

    // Texture loading methods
    const Texture* getTexture(std::string path);
    void loadTexture(const std::string& path);
    
    // Preloading methods
    void preloadTextures();
    void preloadTexturesFromDirectory(const std::string& directory);
    
    // Management methods
    void clear();

private:
    TextureManager() = default;
    ~TextureManager();

    // Delete copy/move constructors and assignments
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    std::unordered_map<std::string, Texture> textureCache;
};

#endif // TEXTURE_MANAGER_HPP
