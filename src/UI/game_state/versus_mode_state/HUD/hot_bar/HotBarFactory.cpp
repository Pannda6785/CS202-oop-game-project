#include "HotBarFactory.hpp"
#include "sun_priestess_hot_bar/SunPriestessHotBar.hpp"
#include "silent_redhood_hot_bar/SilentRedhoodHotBar.hpp"
#include "stormbeast_hot_bar/StormbeastHotBar.hpp"
#include "royal_arcanist_hot_bar/RoyalArcanistHotBar.hpp"
#include "lich_of_flowers/LichOfFlowersHotBar.hpp"
#include "hero_of_frost_hot_bar/HeroOfFrostHotBar.hpp"
#include "dreadwyrm_heir_hot_bar/DreadwyrmHeirHotBar.hpp"
#include "depth_secret_hot_bar/DepthSecretHotBar.hpp"

std::unique_ptr<HotBar> HotBarFactory::createForCharacter(const std::string& characterName, bool isLeftSide) {
    if (characterName == "Priestess") {
        return std::make_unique<SunPriestessHotBar>(isLeftSide);
    }
    else if (characterName == "Redhood") {
        return std::make_unique<SilentRedhoodHotBar>(isLeftSide);
    }
    else if (characterName == "Stormbeast") {
        return std::make_unique<StormbeastHotBar>(isLeftSide);
    }
    else if (characterName == "Arcanist") {
        return std::make_unique<RoyalArcanistHotBar>(isLeftSide);
    }
    else if (characterName == "Lich") {
        return std::make_unique<LichOfFlowersHotBar>(isLeftSide);
    }
    else if (characterName == "Hero") {
        return std::make_unique<HeroOfFrostHotBar>(isLeftSide);
    }
    else if (characterName == "Wyrm") {
        return std::make_unique<DreadwyrmHeirHotBar>(isLeftSide);
    }
    else if (characterName == "Depth") {
        return std::make_unique<DepthSecretHotBar>(isLeftSide);
    }
}