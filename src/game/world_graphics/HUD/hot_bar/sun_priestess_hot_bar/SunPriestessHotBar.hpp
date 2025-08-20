#ifndef SUN_PRIESTESS_HOT_BAR_HPP
#define SUN_PRIESTESS_HOT_BAR_HPP

#include "../HotBar.hpp"

class SunPriestessHotBar : public HotBar {
public:
    SunPriestessHotBar(bool isLeftSide = true);
    ~SunPriestessHotBar() = default;

private:
    const std::vector<std::string> abilityTexturePaths = {
        "../assets/UI_sprites/hot_bar/sun_priestess/basic.png",
        "../assets/UI_sprites/hot_bar/sun_priestess/wide.png",
        "../assets/UI_sprites/hot_bar/sun_priestess/offensive.png",
        "../assets/UI_sprites/hot_bar/sun_priestess/defensive.png"
    };
};

#endif // SUN_PRIESTESS_HOT_BAR_HPP