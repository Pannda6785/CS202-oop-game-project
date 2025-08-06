#include "SilentRedhoodPreview.hpp"

SilentRedhoodPreview::SilentRedhoodPreview() {
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/sun_priestess/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/sun_priestess/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/sun_priestess/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/charselect/sun_priestess_front_tile.png");
    setCharName("Sun Priestess");
    setBackgroundColor({212, 155, 105, 255});
    setRibbonBackgroundColor({214, 70, 62, 255});
    setFrontTileColor({224, 113, 18, 255});
    setMovingTileBackgroundColor({255, 120, 57, 255});
    enter();
}

SilentRedhoodPreview::SilentRedhoodPreview(bool isLeft) : CharSelectPreview() {
    setSide(isLeft);
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/sun_priestess/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/sun_priestess/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/sun_priestess/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Sun Priestess");
    setBackgroundColor({212, 155, 105, 255});
    setRibbonBackgroundColor({214, 70, 62, 255});
    setFrontTileColor({224, 113, 18, 255});
    setMovingTileBackgroundColor({255, 120, 57, 255});
    enter();
}

SilentRedhoodPreview::~SilentRedhoodPreview() = default;

void SilentRedhoodPreview::setSide(bool isLeft) {
    CharSelectPreview::setSide(isLeft);
}