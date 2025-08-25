#include "BehindDots.hpp"
#include "../../../graphics/TextureManager.hpp"
#include <cassert>
#include <random>
#include <algorithm>
#include <iostream>

BehindDots::BehindDots() = default;
BehindDots::~BehindDots() = default;

void BehindDots::loadDotTexture(const std::string& texturePath) {
    dotTexture = TextureManager::instance().getTexture(texturePath);
    loadedDotTexture = dotTexture != nullptr; // Check if the texture is loaded
    assert(loadedDotTexture);
}

void BehindDots::unloadTexture() {
    if (loadedDotTexture) {
        loadedDotTexture = false;
    }
}

void BehindDots::addNewDot(){
    if(!loadedDotTexture) return;
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> randPosX(0, GetScreenWidth());
    static std::uniform_int_distribution<> randPosY(0, GetScreenHeight());
    static std::uniform_int_distribution<> randOffset(-100, 100);
    static std::uniform_int_distribution<> randScale(5.0, 5.0);
    static std::uniform_real_distribution<> randLifeTime(3.0f, 7.0f);
    dots.emplace_back(std::make_unique<BehindDotsGraphicsComponent>());
    dots.back()->init(dotTexture, 
                    {(float)randPosX(gen), (float)randPosY(gen)},
                    randScale(gen),
                    {(float)randOffset(gen), (float)randOffset(gen)},
                    randLifeTime(gen),
                    RED);
}

void BehindDots::init(){
    for(int i = 0; i < numberOfDots; i++){
        addNewDot();
    }
}

void BehindDots::update(float dt) {
    if (!loadedDotTexture) return;

    Color color = getCurrentColor();
    for (auto& dot : dots) {
        dot->update(dt, color);
    }
    dots.erase(std::remove_if(dots.begin(), dots.end(), 
               [](const std::unique_ptr<BehindDotsGraphicsComponent>& dot) { return !dot->exist(); }), 
               dots.end());
    while(dots.size() < numberOfDots){
        addNewDot();
    }
    assert(dots.size() == numberOfDots);
}

Color BehindDots::ColorLerp(Color from, Color to, float t){
    Color result;
    result.r = (unsigned char)(from.r + (to.r - from.r) * t);
    result.g = (unsigned char)(from.g + (to.g - from.g) * t);
    result.b = (unsigned char)(from.b + (to.b - from.b) * t);
    result.a = (unsigned char)(from.a + (to.a - from.a) * t);
    return result;
}

Color BehindDots::getCurrentColor() {
    float time = GetTime();
    int currentIndex = ((int)time) % palette.size();
    int nextIndex = (currentIndex + 1) % palette.size();
    float t = fmodf(time, 1.0f);
    Color color = ColorLerp(palette[currentIndex], palette[nextIndex], t);
    return color;
}

void BehindDots::setVisible(bool visible) {
    for (auto& dot : dots) {
        dot->setVisible(visible);
    }
}