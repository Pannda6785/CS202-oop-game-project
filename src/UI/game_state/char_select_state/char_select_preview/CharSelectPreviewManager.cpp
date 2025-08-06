#include "CharSelectPreviewManager.hpp"

CharSelectPreviewManager::CharSelectPreviewManager() : preview(nullptr)
{
}

CharSelectPreviewManager::~CharSelectPreviewManager() = default;

void CharSelectPreviewManager::init(bool isLeft) {
    this->isLeft = isLeft;
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