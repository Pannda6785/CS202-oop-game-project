#include "DepthSecretPreview.hpp"

DepthSecretPreview::DepthSecretPreview() {
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/depth_secret/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/depth_secret/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/depth_secret/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Depth's Secret");
    setBackgroundColor({157,200,187,255});
    setRibbonBackgroundColor({38,38,38,255});
    setFrontTileColor({29,114,86,255});
    setMovingTileBackgroundColor({40,227,167,255});
    enter();
}

DepthSecretPreview::DepthSecretPreview(bool isLeft) : CharSelectPreview() {
    setSide(isLeft);
    addTextureMainPortrait("../assets/UI_sprites/char_select_preview/depth_secret/main_portrait.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/depth_secret/idle_anim_0.png");
    addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/depth_secret/idle_anim_1.png");
    addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    addTextureFrontTile("../assets/UI_sprites/side_ribbon.png");
    setCharName("Depth's Secret");
    setBackgroundColor({157,200,187,255});
    setRibbonBackgroundColor({38,38,38,255});
    setFrontTileColor({29,114,86,255});
    setMovingTileBackgroundColor({40,227,167,255});
    enter();
}

DepthSecretPreview::~DepthSecretPreview() = default;

void DepthSecretPreview::setSide(bool isLeft) {
    CharSelectPreview::setSide(isLeft);
}