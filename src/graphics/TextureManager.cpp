#include "TextureManager.hpp"

#include <iostream>
#include <algorithm>
#include <filesystem>
#include <chrono>

// Helper function to check if a string ends with a certain suffix
bool endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) {
        return false;
    }
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

TextureManager& TextureManager::instance() {
    static TextureManager instance;
    return instance;
}

void TextureManager::preloadTextures() {
    // Record start time for performance measurement
    auto startTime = std::chrono::high_resolution_clock::now();
    
    int loadedCount = 0;
    std::cout << "Starting texture preloading process..." << std::endl;
    
    // Preload all PNG files from the assets directory
    preloadTexturesFromDirectory("../assets");
    
    // Calculate and print the time taken
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    std::cout << "Texture preloading complete. Loaded " << textureCache.size() 
              << " textures in " << duration << "ms." << std::endl;
}

void TextureManager::preloadTexturesFromDirectory(const std::string& directory) {
    try {
        // Make sure the directory exists
        if (!std::filesystem::exists(directory)) {
            std::cerr << "Warning: Directory does not exist: " << directory << std::endl;
            return;
        }
        
        // Recursively iterate through all files in the directory
        for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                std::string path = entry.path().string();
                
                // Convert path to lowercase for case-insensitive comparison
                std::string lowerPath = path;
                std::transform(lowerPath.begin(), lowerPath.end(), lowerPath.begin(), 
                               [](unsigned char c) { return std::tolower(c); });
                
                // Check if the file is a PNG
                if (endsWith(lowerPath, ".png")) {
                    // Use forward slashes for consistency
                    std::replace(path.begin(), path.end(), '\\', '/');
                    
                    // Load the texture
                    loadTexture(path);
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error during texture preloading: " << e.what() << std::endl;
    }
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

void TextureManager::loadTexture(const std::string& path) {
    // Skip if already loaded
    if (textureCache.find(path) != textureCache.end()) {
        return;
    }
    
    // Load the texture
    Texture texture = LoadTexture(path.c_str());
    if (texture.id == 0) {
        std::cerr << "Warning: TextureManager - Failed to load texture: " << path << std::endl;
        return;
    }
    
    // Store in cache
    textureCache[path] = texture;
    
    // Uncomment for verbose logging
    // std::cout << "Loaded texture: " << path << std::endl;
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
