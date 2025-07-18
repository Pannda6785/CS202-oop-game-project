#include "BehindDotsGraphicsComponent.hpp"
#include <iostream>
#include <cassert>
#include <vector>

BehindDotsGraphicsComponent::BehindDotsGraphicsComponent() = default;

BehindDotsGraphicsComponent::~BehindDotsGraphicsComponent(){
    dotTexture = nullptr; // Reset the pointer to avoid dangling references
}

void BehindDotsGraphicsComponent::init(const Texture *_dotTexture, const Vector2& _position, float _scale, const Vector2& _offset, float _lifeTime, Color _color) {
    dotTexture = _dotTexture;
    position = _position;
    scale = _scale;
    offset = _offset;
    loadedDotTexture = (dotTexture && dotTexture->id != 0); // Check if the texture is loaded
    color = _color; // Default color
    lifeTime = _lifeTime;
    setLayer(1);
    for(int i = 0; i < 2; i++) timer[i] = 0.0f;
}

void BehindDotsGraphicsComponent::update(float dt, Color color) {
    // Update logic can be added here if needed
    this->color = color; // Update the color if needed
    position.x += offset.x * dt;
    position.y += offset.y * dt;
    if(timer[0] < lifeTime){
        this->color.a = static_cast<unsigned char>(255.0f * timer[0] / lifeTime);
        timer[0] += dt;
    } else{
        if(lifeTime > timer[1]) this->color.a = static_cast<unsigned char>(255.0f * (lifeTime - timer[1]) / lifeTime);
        timer[1] += dt;
    }
}

void BehindDotsGraphicsComponent::render() const {
    if (!isVisible() || !loadedDotTexture || !dotTexture) return;
    if(dotTexture && dotTexture->id != 0 && timer[0] > 0){
        DrawTexture(*dotTexture, position.x, position.y, color);
    }
}

bool BehindDotsGraphicsComponent::exist() const {
    return position.x >= 0 && position.x <= GetScreenWidth() &&
           position.y >= 0 && position.y <= GetScreenHeight() &&
           lifeTime >= timer[1];
}