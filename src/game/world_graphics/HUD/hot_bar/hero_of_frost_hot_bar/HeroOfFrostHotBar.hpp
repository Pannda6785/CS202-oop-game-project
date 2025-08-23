#ifndef HERO_OF_FROST_HOT_BAR_HPP
#define HERO_OF_FROST_HOT_BAR_HPP

#include "../HotBar.hpp"

class HeroOfFrostHotBar : public HotBar {
public:
    HeroOfFrostHotBar(bool isLeftSide = true);
    ~HeroOfFrostHotBar() = default;

private:
    const std::vector<std::string> abilityTexturePaths = {
        "../assets/UI_sprites/hot_bar/hero_of_frost/basic.png",
        "../assets/UI_sprites/hot_bar/hero_of_frost/wide.png",
        "../assets/UI_sprites/hot_bar/hero_of_frost/offensive.png",
        "../assets/UI_sprites/hot_bar/hero_of_frost/defensive.png"
    };
};

#endif // HERO_OF_FROST_HOT_BAR_HPP