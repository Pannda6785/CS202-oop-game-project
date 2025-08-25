#include "Artwork.hpp"
#include "../../../../graphics/TextureManager.hpp"
#include <raylib.h>
#include <iostream>
#include <cassert>
#include <unordered_map>

Artwork::Artwork() : GraphicsComponent(), 
period(1.0f), posX(0), posY(0), drawWidth(0), drawHeight(0), 
scale(1.0f), fadeInTime(0.0f), fadeInTimer(0.0f), middle(false), flip(false),
flipVertical(false), flipHorizontal(false), shaderEnabled(false), shaderLoaded(false) {
}

Artwork::~Artwork(){
    unloadTextures();
    unloadShader();
}

void Artwork::unloadTextures() {
    // Texture management is handled by TextureManager
}

void Artwork::unloadShader() {
    if (shaderLoaded) {
        UnloadShader(shader);
        shaderLoaded = false;
        shaderEnabled = false;
    }
}

void Artwork::loadShader(const std::string& fragmentShaderPath) {
    // Unload any existing shader
    unloadShader();
    
    // Load the new shader (null vertex shader, fragment shader from file)
    shader = LoadShader(0, fragmentShaderPath.c_str());
    shaderPath = fragmentShaderPath;
    
    if (shader.id > 0) {
        shaderLoaded = true;
        std::cout << "Shader loaded successfully: " << fragmentShaderPath << std::endl;
    } else {
        std::cerr << "Failed to load shader: " << fragmentShaderPath << std::endl;
    }
}

void Artwork::enableShader(bool enable) {
    shaderEnabled = enable && shaderLoaded;
}

void Artwork::setShaderValue(const std::string& uniformName, const void* value, int uniformType) {
    if (!shaderLoaded) {
        std::cerr << "Cannot set shader value: no shader loaded" << std::endl;
        return;
    }
    
    // Get or cache the uniform location
    int location;
    auto it = uniformLocations.find(uniformName);
    if (it == uniformLocations.end()) {
        location = GetShaderLocation(shader, uniformName.c_str());
        uniformLocations[uniformName] = location;
    } else {
        location = it->second;
    }
    
    if (location != -1) {
        SetShaderValue(shader, location, value, uniformType);
    } else {
        std::cerr << "Uniform not found: " << uniformName << std::endl;
    }
}

bool Artwork::hasShader() const {
    return shaderLoaded;
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
    flipVertical = flipHorizontal = false;
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

void Artwork::setFlipVertical(bool flipVertical) {
    this->flipVertical = flipVertical;
    if(flipVertical) originRatio.x = 1.0f - originRatio.x;
}

void Artwork::setFlipHorizontal(bool flipHorizontal) {
    this->flipHorizontal = flipHorizontal;
    if(flipHorizontal) originRatio.y = 1.0f - originRatio.y;
}

void Artwork::setOriginRatio(Vector2 originRatio) {
    this->originRatio = originRatio;
}

void Artwork::setAlphaColor(float alpha) {
    if (textures.empty() || textures[0] == nullptr) return;
    alphaColor = alpha;
}

void Artwork::setColor(Color color){
    this->color = color;
}

float Artwork::getFadeInTime() const {
    return fadeInTime;
}

float Artwork::getFadeInTimer() const {
    return fadeInTimer;
}

void Artwork::update(float dt) {
    if(timer == -1.0f) timer = 0.0f;
    timer += dt;
    if (fadeInTime > 0.0f) {
        fadeInTimer += dt;
        if (fadeInTimer > fadeInTime) {
            fadeInTimer = fadeInTime;
        }
    }
    
    // If shader is enabled and has a time uniform, update it automatically
    if (shaderEnabled && shaderLoaded) {
        float currentTime = GetTime();
        auto it = uniformLocations.find("time");
        int timeLoc = GetShaderLocation(shader, "time");
        SetShaderValue(shader, timeLoc, &currentTime, SHADER_UNIFORM_FLOAT);
        // if (it != uniformLocations.end() && it->second != -1) {
        //     SetShaderValue(shader, it->second, &currentTime, SHADER_UNIFORM_FLOAT);
        // }
    }
}

void Artwork::render() const {
    if (textures.empty() || textures[0] == nullptr) return;
    
    const Texture2D* tex = textures[static_cast<int>((timer == -1.0f ? GetTime() : timer) / period) % textures.size()];
    int w = drawWidth > 0 ? drawWidth : tex->width;
    int h = drawHeight > 0 ? drawHeight : tex->height;
    Rectangle source = { 0, 0, (float)tex->width, (float)tex->height };
    Rectangle dest = { posX, posY, tex->width * scale, tex->height * scale };
    float rotation = 0;
    Color _color = { color.r, color.g, color.b, color.a * (fadeInTime > 0.0f ? fadeInTimer / fadeInTime : alphaColor) };
    
    if(flip) source.width = -source.width;
    if(flipHorizontal) {
        source.height = -source.height;
    }
    if(flipVertical) {
        source.width = -source.width;
    }
    
    Vector2 origin = { originRatio.x * tex->width * scale, originRatio.y * tex->height * scale };
    
    // Use shader if enabled
    if (shaderEnabled && shaderLoaded) {
        BeginShaderMode(shader);
        DrawTexturePro(*tex, source, dest, origin, rotation, _color);
        EndShaderMode();
    } else {
        DrawTexturePro(*tex, source, dest, origin, rotation, _color);
    }
}