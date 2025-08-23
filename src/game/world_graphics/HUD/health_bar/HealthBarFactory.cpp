#include "HealthBarFactory.hpp"
#include "sun_priestess_health_bar/SunPriestessHealthBar.hpp"
#include "silent_redhood_health_bar/SilentRedhoodHealthBar.hpp"
#include "stormbeast_health_bar/StormbeastHealthBar.hpp"
#include "royal_arcanist_health_bar/RoyalArcanistHealthBar.hpp"
#include "lich_of_flowers_health_bar/LichOfFlowersHealthBar.hpp"
#include "hero_of_frost_health_bar/HeroOfFrostHealthBar.hpp"
#include "dreadwyrm_heir_health_bar/DreadwyrmHeirHealthBar.hpp"
#include "depth_secret_health_bar/DepthSecretHealthBar.hpp"

#include <algorithm>
#include <stdexcept>

std::unique_ptr<HealthBar> HealthBarFactory::createForCharacter(const std::string& characterName, bool isLeftSide) {
    if (characterName == "Priestess") {
        return std::make_unique<SunPriestessHealthBar>(isLeftSide);
    }
    else if (characterName == "Redhood") {
        return std::make_unique<SilentRedhoodHealthBar>(isLeftSide);
    }
    else if (characterName == "Stormbeast") {
        return std::make_unique<StormbeastHealthBar>(isLeftSide);
    }
    else if (characterName == "Arcanist") {
        return std::make_unique<RoyalArcanistHealthBar>(isLeftSide);
    }
    else if (characterName == "Lich") {
        return std::make_unique<LichOfFlowersHealthBar>(isLeftSide);
    }
    else if (characterName == "Hero") {
        return std::make_unique<HeroOfFrostHealthBar>(isLeftSide);
    }
    else if (characterName == "Wyrm") {
        return std::make_unique<DreadwyrmHeirHealthBar>(isLeftSide);
    }
    else if (characterName == "Depth") {
        return std::make_unique<DepthSecretHealthBar>(isLeftSide);
    }
    return std::make_unique<HealthBar>(isLeftSide);
}