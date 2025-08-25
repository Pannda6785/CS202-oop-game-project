#include "CustomCursor.hpp"

CustomCursor& CustomCursor::getInstance() {
    static CustomCursor instance;
    return instance;
}

CustomCursor::~CustomCursor() {
    graphic.unloadTextures();
}

void CustomCursor::init(){
    graphic.loadClickTexture("../assets/UI_sprites/click_cursor.png");
    graphic.loadNormalTexture("../assets/UI_sprites/normal_cursor.png");
    graphic.loadArroundDotTexture("../assets/UI_sprites/decoration/arround_dot.png");
}

void CustomCursor::update(float dt){
    graphic.update(dt);
}