#include "CustomCursor.hpp"

CustomCursor& CustomCursor::getInstance() {
    static CustomCursor instance;
    return instance;
}

void CustomCursor::init(){
    graphic.loadClickTexture("../assets/UI_sprites/new_click_cursor.png");
    graphic.loadNormalTexture("../assets/UI_sprites/new_normal_cursor.png");
}