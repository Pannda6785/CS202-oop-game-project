#include "CharSelectPreviewManager.hpp"

CharSelectPreviewManager::CharSelectPreviewManager() {
    init();
}

CharSelectPreviewManager::~CharSelectPreviewManager() {
    // Clean up resources if needed
}

void CharSelectPreviewManager::init(bool isLeft) {
    this->isLeft = isLeft;
    // sunPriestessPreview = std::make_shared<CharSelectPreview>();
    // sunPriestessPreview->addTextureMainPortrait("../assets/UI_sprites/char_select_preview/sun_priestess/main_portrait.png");
    // sunPriestessPreview->addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/sun_priestess/idle_anim_0.png");
    // sunPriestessPreview->addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/sun_priestess/idle_anim_1.png");
    // sunPriestessPreview->addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    // sunPriestessPreview->addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    // sunPriestessPreview->addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    // sunPriestessPreview->addTextureFrontTile("../assets/charselect/sun_priestess_front_tile.png");
    // sunPriestessPreview->setSide(isLeft);
    // sunPriestessPreview->setCharName("Sun Priestess");
    // sunPriestessPreview->setBackgroundColor({212, 155, 105, 255});
    // sunPriestessPreview->setRibbonBackgroundColor({214, 70, 62, 255});
    // sunPriestessPreview->setFrontTileColor({224, 113, 18, 255});
    // sunPriestessPreview->enter();

    // silentRedhoodPreview = std::make_shared<CharSelectPreview>();
    // silentRedhoodPreview->addTextureMainPortrait("../assets/UI_sprites/char_select_preview/sun_priestess/main_portrait.png");
    // silentRedhoodPreview->addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/sun_priestess/idle_anim_0.png");
    // silentRedhoodPreview->addTextureIdleAnimPreview("../assets/UI_sprites/char_select_preview/sun_priestess/idle_anim_1.png");
    // silentRedhoodPreview->addTextureBackgroundTiles(0, "../assets/UI_sprites/char_select_preview/ribbon.png");
    // silentRedhoodPreview->addTextureBackgroundTiles(1, "../assets/UI_sprites/char_select_preview/ribbon.png");
    // silentRedhoodPreview->addTextureBackgroundTiles(2, "../assets/UI_sprites/char_select_preview/ribbon.png");
    // silentRedhoodPreview->addTextureFrontTile("../assets/charselect/sun_priestess_front_tile.png");
    // silentRedhoodPreview->setSide(isLeft);
    // silentRedhoodPreview->setCharName("Sun Priestess");
    // silentRedhoodPreview->setBackgroundColor({212, 155, 105, 255});
    // silentRedhoodPreview->setRibbonBackgroundColor({214, 70, 62, 255});
    // silentRedhoodPreview->setFrontTileColor({224, 113, 18, 255});
    // silentRedhoodPreview->enter();


    preview = std::make_unique<SunPriestessPreview>(isLeft);
}

void CharSelectPreviewManager::setPreview(std::string characterName, bool isLeft) {
    if (characterName == "Sun Priestess") {
        preview = std::make_unique<SunPriestessPreview>(isLeft);
    } else if (characterName == "Silent Redhood") {
        preview = std::make_unique<SilentRedhoodPreview>(isLeft);
    }
}

void CharSelectPreviewManager::update(float dt) {
    if (preview) {
        preview->update(dt);
    }
}