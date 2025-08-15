#include "GameText.hpp"
#include <raylib.h>
#include <iostream>

GameText::GameText() : GraphicsComponent(), font(GetFontDefault()), fontLoaded(false), 
                      x(0), y(0), fontSize(32), color(WHITE),
                      shaderEnabled(false), shaderLoaded(false), time(0.0f) {}

GameText::~GameText() {
    if (fontLoaded) {
        UnloadFont(font);
    }
    unloadShader();
}

void GameText::setText(const std::string& t) {
    text = t;
}

void GameText::loadFont(const std::string& fontPath) {
    if (fontLoaded) {
        UnloadFont(font);
        fontLoaded = false;
    }
    font = LoadFontEx(fontPath.c_str(), 256, nullptr, 0);
    fontLoaded = font.texture.id != 0;
}

void GameText::unloadFont() {
    if (fontLoaded) {
        UnloadFont(font);
        fontLoaded = false;
    }
}

// New shader methods
void GameText::loadShader(const std::string& fragmentShaderPath) {
    // Unload any existing shader
    unloadShader();
    
    // Load the new shader (null vertex shader, fragment shader from file)
    shader = LoadShader(0, fragmentShaderPath.c_str());
    shaderPath = fragmentShaderPath;
    
    if (shader.id > 0) {
        shaderLoaded = true;
        std::cout << "Text shader loaded successfully: " << fragmentShaderPath << std::endl;
    } else {
        std::cerr << "Failed to load text shader: " << fragmentShaderPath << std::endl;
    }
}

void GameText::enableShader(bool enable) {
    shaderEnabled = enable && shaderLoaded;
}

void GameText::setShaderValue(const std::string& uniformName, const void* value, int uniformType) {
    if (!shaderLoaded) {
        std::cerr << "Cannot set text shader value: no shader loaded" << std::endl;
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
        std::cerr << "Text shader uniform not found: " << uniformName << std::endl;
    }
}

bool GameText::hasShader() const {
    return shaderLoaded;
}

void GameText::unloadShader() {
    if (shaderLoaded) {
        UnloadShader(shader);
        shaderLoaded = false;
        shaderEnabled = false;
    }
}

void GameText::update(float dt) {
    // Update shader time if needed
    if (shaderEnabled && shaderLoaded) {
        float currentTime = GetTime();
        int timeLoc = GetShaderLocation(shader, "time");
        if (timeLoc != -1) {
            SetShaderValue(shader, timeLoc, &currentTime, SHADER_UNIFORM_FLOAT);
        }
    }
}

void GameText::setPosition(int px, int py) {
    x = px;
    y = py;
}

void GameText::setColor(Color c) {
    color = c;
}

void GameText::setFontSize(int size) {
    fontSize = size;
}

void GameText::setOriginRatio(Vector2 originRatio) {
    this->originRatio = originRatio;
}

void GameText::setAlphaColor(float alpha) {
    color.a = static_cast<unsigned char>(alpha * 255);
}

void GameText::setAngle(float angle) {
    this->angle = angle;
}

const std::string& GameText::getText() const {
    return text;
}

int GameText::getX() const {
    return x;
}

int GameText::getY() const {
    return y;
}

int GameText::getFontSize() const {
    return fontSize;
}

Color GameText::getColor() const {
    return color;
}

float GameText::getWidth() const {
    if (fontLoaded) {
        return MeasureTextEx(font, text.c_str(), (float)fontSize, 1).x;
    } else {
        return MeasureText(text.c_str(), fontSize);
    }
}

float GameText::getHeight() const {
    if (fontLoaded) {
        return MeasureTextEx(font, text.c_str(), (float)fontSize, 1).y;
    } else {
        return fontSize; // Default height based on font size
    }
}

void GameText::render() const {
    if (text.empty()) return;
    
    Vector2 origin = {originRatio.x * getWidth(), originRatio.y * getHeight()};
    
    // Use shader if enabled
    if (shaderEnabled && shaderLoaded) {
        BeginShaderMode(shader);
        if (fontLoaded) {
            DrawTextPro(font, text.c_str(), {(float)x, (float)y}, origin, angle, fontSize, 1, color);
        } else {
            DrawText(text.c_str(), x - origin.x, y - origin.y, fontSize, color);
        }
        EndShaderMode();
    } else {
        if (fontLoaded) {
            DrawTextPro(font, text.c_str(), {(float)x, (float)y}, origin, angle, fontSize, 1, color);
        } else {
            DrawText(text.c_str(), x - origin.x, y - origin.y, fontSize, color);
        }
    }
}