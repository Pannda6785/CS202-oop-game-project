#ifndef ROYAL_ARCANIST_HOT_BAR_HPP
#define ROYAL_ARCANIST_HOT_BAR_HPP

#include "../HotBar.hpp"

class RoyalArcanistHotBar : public HotBar {
public:
    RoyalArcanistHotBar(bool isLeftSide = true);
    ~RoyalArcanistHotBar() = default;

private:
    const std::vector<std::string> abilityTexturePaths = {
        "../assets/UI_sprites/hot_bar/royal_arcanist/basic.png",
        "../assets/UI_sprites/hot_bar/royal_arcanist/wide.png",
        "../assets/UI_sprites/hot_bar/royal_arcanist/offensive.png",
        "../assets/UI_sprites/hot_bar/royal_arcanist/defensive_1.png",
        "../assets/UI_sprites/hot_bar/royal_arcanist/defensive_2.png"
    };
};

#endif // ROYAL_ARCANIST_HOT_BAR_HPP