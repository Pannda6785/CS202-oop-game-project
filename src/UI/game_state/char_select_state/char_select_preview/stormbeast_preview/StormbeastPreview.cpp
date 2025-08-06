#include "StormbeastPreview.hpp"

StormbeastPreview::StormbeastPreview() {
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/stormbeast/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/stormbeast/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/stormbeast/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Stormbeast");
    setBackgroundColor({130,115,152,255});
    setRibbonBackgroundColor({205,188,231,255});
    setFrontTileColor({86,85,104,255});
    setMovingTileBackgroundColor({162,133,249,255});
    enter();
}

StormbeastPreview::StormbeastPreview(bool isLeft) : CharSelectPreview() {
    setSide(isLeft);
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/stormbeast/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/stormbeast/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/stormbeast/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Stormbeast");
    setBackgroundColor({130,115,152,255});
    setRibbonBackgroundColor({205,188,231,255});
    setFrontTileColor({86,85,104,255});
    setMovingTileBackgroundColor({162,133,249,255});
    enter();
}

StormbeastPreview::~StormbeastPreview() = default;

void StormbeastPreview::setSide(bool isLeft) {
    CharSelectPreview::setSide(isLeft);
}