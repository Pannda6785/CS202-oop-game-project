#include "CharSelectPreviewManager.hpp"
#include "./sun_priestess_preview/SunPriestessPreview.hpp"
#include "./silent_redhood_preview/SilentRedhoodPreview.hpp"
#include "./depth_secret_preview/DepthSecretPreview.hpp"
#include "./dreadwyrm_heir_preview/DreadwyrmHeirPreview.hpp"
#include "./hero_of_frost_preview/HeroOfFrostPreview.hpp"
#include "./lich_of_flowers_preview/LichOfFlowersPreview.hpp"
#include "./royal_arcanist_preview/RoyalArcanistPreview.hpp"
#include "./stormbeast_preview/StormbeastPreview.hpp"   
#include "./random_char_preview/RandomCharPreview.hpp"

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
    } else if (characterName == "Depth's Secret") {
        preview = std::make_unique<DepthSecretPreview>(isLeft);
    } else if (characterName == "Dreadwyrm Heir") {
        preview = std::make_unique<DreadwyrmHeirPreview>(isLeft);
    } else if (characterName == "Hero of Frost") {
        preview = std::make_unique<HeroOfFrostPreview>(isLeft);
    } else if (characterName == "Lich of Flowers") {
        preview = std::make_unique<LichOfFlowersPreview>(isLeft);
    } else if (characterName == "Royal Arcanist") {
        preview = std::make_unique<RoyalArcanistPreview>(isLeft);
    } else if (characterName == "Stormbeast") {
        preview = std::make_unique<StormbeastPreview>(isLeft);
    } else if (characterName == "Random Select") {
        preview = std::make_unique<RandomCharPreview>(isLeft);
    } else {
        preview = std::make_unique<SunPriestessPreview>(isLeft);
    }
}

void CharSelectPreviewManager::update(float dt) {
    if (preview) {
        preview->update(dt);
    }
}