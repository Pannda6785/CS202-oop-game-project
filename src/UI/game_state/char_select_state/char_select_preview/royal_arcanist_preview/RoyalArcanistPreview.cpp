#include "RoyalArcanistPreview.hpp"

RoyalArcanistPreview::RoyalArcanistPreview() {
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/royal_arcanist/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/royal_arcanist/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/royal_arcanist/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Royal Arcanist");
    setBackgroundColor({95,97,101,255});
    setRibbonBackgroundColor({32,29,29,255});
    setFrontTileColor({99,39,36,255});
    setMovingTileBackgroundColor({66,66,66,255});
    enter();
}

RoyalArcanistPreview::RoyalArcanistPreview(bool isLeft) : CharSelectPreview() {
    setSide(isLeft);
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/royal_arcanist/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/royal_arcanist/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/royal_arcanist/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Royal Arcanist");
    setBackgroundColor({95,97,101,255});
    setRibbonBackgroundColor({32,29,29,255});
    setFrontTileColor({99,39,36,255});
    setMovingTileBackgroundColor({66,66,66,255});
    enter();
}

RoyalArcanistPreview::~RoyalArcanistPreview() = default;

void RoyalArcanistPreview::setSide(bool isLeft) {
    CharSelectPreview::setSide(isLeft);
}