#include "LichOfFlowersPreview.hpp"

LichOfFlowersPreview::LichOfFlowersPreview() {
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/lich_of_flowers/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/lich_of_flowers/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/lich_of_flowers/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Lich of Flowers");
    setBackgroundColor({100,104,142,255});
    setRibbonBackgroundColor({25,25,27,255});
    setFrontTileColor({27,49,123,255});
    setMovingTileBackgroundColor({37,80,221,255});
    enter();
}

LichOfFlowersPreview::LichOfFlowersPreview(bool isLeft) : CharSelectPreview() {
    setSide(isLeft);
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/lich_of_flowers/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/lich_of_flowers/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/lich_of_flowers/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Lich of Flowers");
    setBackgroundColor({100,104,142,255});
    setRibbonBackgroundColor({25,25,27,255});
    setFrontTileColor({27,49,123,255});
    setMovingTileBackgroundColor({37,80,221,255});
    enter();
}

LichOfFlowersPreview::~LichOfFlowersPreview() = default;

void LichOfFlowersPreview::setSide(bool isLeft) {
    CharSelectPreview::setSide(isLeft);
}