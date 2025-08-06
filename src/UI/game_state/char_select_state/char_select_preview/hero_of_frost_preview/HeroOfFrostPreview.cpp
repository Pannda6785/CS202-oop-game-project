#include "HeroOfFrostPreview.hpp"

HeroOfFrostPreview::HeroOfFrostPreview() {
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/hero_of_frost/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/hero_of_frost/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/hero_of_frost/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Hero of Frost");
    setBackgroundColor({110,137,105,255});
    setRibbonBackgroundColor({52,44,40,255});
    setFrontTileColor({102,123,78,255});
    setMovingTileBackgroundColor({155,255,105,255});
    enter();
}

HeroOfFrostPreview::HeroOfFrostPreview(bool isLeft) : CharSelectPreview() {
    setSide(isLeft);
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/hero_of_frost/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/hero_of_frost/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/hero_of_frost/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Hero of Frost");
    setBackgroundColor({110,137,105,255});
    setRibbonBackgroundColor({52,44,40,255});
    setFrontTileColor({102,123,78,255});
    setMovingTileBackgroundColor({155,255,105,255});
    enter();
}

HeroOfFrostPreview::~HeroOfFrostPreview() = default;

void HeroOfFrostPreview::setSide(bool isLeft) {
    CharSelectPreview::setSide(isLeft);
}