#include "CustomCursorGraphicsComponent.hpp"
#include <random>
#include <algorithm>

CustomCursorGraphicsComponent::CustomCursorGraphicsComponent() = default;

CustomCursorGraphicsComponent::~CustomCursorGraphicsComponent(){

}

void CustomCursorGraphicsComponent::loadNormalTexture(const std::string &texturePath){
    normalCursorTexture = LoadTexture(texturePath.c_str());
    isNormalLoaded = normalCursorTexture.id != 0;
    setLayer(100);
}

void CustomCursorGraphicsComponent::loadClickTexture(const std::string &texturePath){
    clickCursorTexture = LoadTexture(texturePath.c_str());
    isClickLoaded = clickCursorTexture.id != 0;
}

void CustomCursorGraphicsComponent::loadArroundDotTexture(const std::string &texturePath){
    arroundDotTexture = LoadTexture(texturePath.c_str());
    isArroundDotLoaded = arroundDotTexture.id != 0;
}

void CustomCursorGraphicsComponent::unloadTextures() {
    if(isNormalLoaded) UnloadTexture(normalCursorTexture);
    if(isClickLoaded) UnloadTexture(clickCursorTexture);
    if(isArroundDotLoaded) UnloadTexture(arroundDotTexture);
}

void CustomCursorGraphicsComponent::render() const{
    Vector2 pos = GetMousePosition();
    for(auto &dot : arroundDots) {
        if(isArroundDotLoaded) {
            // DrawTexture(arroundDotTexture, pos.x * 50.0f * (arroundDots - dot.second) / arroundDots + dot.first.first.x, pos.y * 50.0f * (arroundDots - dot.second) / arroundDots + dot.first.y, (Color){255, 255, 255, dot.second / arroundDotTime * 255});
            DrawTexture(arroundDotTexture, dot.first.first.x, dot.first.first.y, (Color){255, 255, 255, (unsigned char)(dot.second / arroundDotTime * 255)});
        }
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        if(isClickLoaded) DrawTexture(clickCursorTexture, pos.x, pos.y, WHITE);
    } else{
        if(isNormalLoaded) DrawTexture(normalCursorTexture, pos.x, pos.y, WHITE);
    }
}

void CustomCursorGraphicsComponent::update(float dt){
    if (arroundDots.size() > 0) {
        for (auto& dot : arroundDots) {
            dot.second -= dt;
            dot.first.first.x += dot.first.second.x * dt;
            dot.first.first.y += dot.first.second.y * dt;
        }
        arroundDots.erase(std::remove_if(arroundDots.begin(), arroundDots.end(),
                                        [](const std::pair<std::pair<Vector2, Vector2>, float>& dot) { return dot.second <= 0; }),
                        arroundDots.end());
    }
    Vector2 mouseDelta = GetMouseDelta();
    if((mouseDelta.x != 0 || mouseDelta.y != 0)) {
        spawnTimer += dt;
        if(spawnTimer < spawnTime) return;
        spawnTimer = 0.0f;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> rand_number(5, 7);
        std::uniform_int_distribution<> rand_delta(-30.f, 30.f);
        std::uniform_real_distribution<> rand_time(0.0f, 1.0f);
        int number = rand_number(gen);
        Vector2 mousePos = GetMousePosition();
        for(int i = 0; i < number; i++){
            arroundDots.emplace_back(
                std::make_pair(Vector2{mousePos.x + static_cast<float>(rand_delta(gen)), mousePos.y + static_cast<float>(rand_delta(gen))}, 
                               Vector2{static_cast<float>(rand_delta(gen)), static_cast<float>(rand_delta(gen))}),
                arroundDotTime * rand_time(gen)
            );
        }
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> rand_number(15, 20);
        std::uniform_int_distribution<> rand_delta(-30.f, 30.f);
        std::uniform_real_distribution<> rand_time(0.0f, 1.0f);
        int number = rand_number(gen);
        Vector2 mousePos = GetMousePosition();
        for(int i = 0; i < number; i++){
            arroundDots.emplace_back(
                std::make_pair(Vector2{mousePos.x + static_cast<float>(rand_delta(gen)), mousePos.y + static_cast<float>(rand_delta(gen))}, 
                               Vector2{static_cast<float>(rand_delta(gen)), static_cast<float>(rand_delta(gen))}),
                arroundDotTime * rand_time(gen)
            );
        }
    }
}