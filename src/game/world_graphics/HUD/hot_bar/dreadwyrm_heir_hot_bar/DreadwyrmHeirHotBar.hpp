#ifndef DREADWYRM_HEIR_HOT_BAR_HPP
#define DREADWYRM_HEIR_HOT_BAR_HPP

#include "../HotBar.hpp"

class DreadwyrmHeirHotBar : public HotBar {
public:
    DreadwyrmHeirHotBar(bool isLeftSide = true);
    ~DreadwyrmHeirHotBar() = default;

private:
    const std::vector<std::string> abilityTexturePaths = {
        "../assets/UI_sprites/hot_bar/dreadwyrm_heir/basic.png",
        "../assets/UI_sprites/hot_bar/dreadwyrm_heir/wide.png",
        "../assets/UI_sprites/hot_bar/dreadwyrm_heir/offensive.png",
        "../assets/UI_sprites/hot_bar/dreadwyrm_heir/defensive.png"
    };
};

#endif // DREADWYRM_HEIR_HOT_BAR_HPP