#include "DreadwyrmHeirPreview.hpp"

DreadwyrmHeirPreview::DreadwyrmHeirPreview() {
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/dreadwyrm_heir/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/dreadwyrm_heir/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/dreadwyrm_heir/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Dreadwyrm Heir");
    setBackgroundColor({176,148,106,255});
    setRibbonBackgroundColor({205,195,174,255});
    setFrontTileColor({80,84,76,255});
    setMovingTileBackgroundColor({255,236,159,255});
    enter();
}

DreadwyrmHeirPreview::DreadwyrmHeirPreview(bool isLeft) : CharSelectPreview() {
    setSide(isLeft);
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/dreadwyrm_heir/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/dreadwyrm_heir/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/dreadwyrm_heir/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Dreadwyrm Heir");
    setBackgroundColor({176,148,106,255});
    setRibbonBackgroundColor({205,195,174,255});
    setFrontTileColor({80,84,76,255});
    setMovingTileBackgroundColor({255,236,159,255});
    enter();
}

DreadwyrmHeirPreview::~DreadwyrmHeirPreview() = default;

void DreadwyrmHeirPreview::setSide(bool isLeft) {
    CharSelectPreview::setSide(isLeft);
}