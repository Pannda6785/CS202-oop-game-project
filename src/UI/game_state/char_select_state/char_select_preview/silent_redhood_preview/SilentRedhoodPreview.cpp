#include "SilentRedhoodPreview.hpp"

SilentRedhoodPreview::SilentRedhoodPreview() {
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/silent_redhood/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/silent_redhood/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/silent_redhood/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Silent Redhood");
    setBackgroundColor({193, 59, 76, 255});
    setRibbonBackgroundColor({172, 55, 59, 255});
    setFrontTileColor({58, 35, 36, 255});
    setMovingTileBackgroundColor({220, 47, 55, 255});
    enter();
}

SilentRedhoodPreview::SilentRedhoodPreview(bool isLeft) : CharSelectPreview() {
    setSide(isLeft);
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/silent_redhood/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/silent_redhood/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/silent_redhood/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");

    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Silent Redhood");
    setBackgroundColor({193, 59, 76, 255});
    setRibbonBackgroundColor({172, 55, 59, 255});
    setFrontTileColor({58, 35, 36, 255});
    setMovingTileBackgroundColor({220, 47, 55, 255});
    enter();
}

SilentRedhoodPreview::~SilentRedhoodPreview() = default;

void SilentRedhoodPreview::setSide(bool isLeft) {
    CharSelectPreview::setSide(isLeft);
}