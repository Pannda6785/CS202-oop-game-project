#include "CustomCursorGraphicsComponent.hpp"

CustomCursorGraphicsComponent::CustomCursorGraphicsComponent() = default;

CustomCursorGraphicsComponent::~CustomCursorGraphicsComponent(){

}

void CustomCursorGraphicsComponent::loadNormalTexture(const std::string &texturePath){
    normalCursorTexture = LoadTexture(texturePath.c_str());
    isNormalLoaded = normalCursorTexture.id != 0;
}

void CustomCursorGraphicsComponent::loadClickTexture(const std::string &texturePath){
    clickCursorTexture = LoadTexture(texturePath.c_str());
    isClickLoaded = clickCursorTexture.id != 0;
}

void CustomCursorGraphicsComponent::render() const{
    Vector2 pos = GetMousePosition();
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        if(isClickLoaded) DrawTexture(clickCursorTexture, pos.x, pos.y, WHITE);
    } else{
        if(isNormalLoaded) DrawTexture(normalCursorTexture, pos.x, pos.y, WHITE);
    }
}