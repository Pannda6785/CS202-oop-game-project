#ifndef LICH_OF_FLOWERS_HOT_BAR_HPP
#define LICH_OF_FLOWERS_HOT_BAR_HPP

#include "../HotBar.hpp"

class LichOfFlowersHotBar : public HotBar {
public:
    LichOfFlowersHotBar(bool isLeftSide = true);
    ~LichOfFlowersHotBar() = default;

private:
    const std::vector<std::string> abilityTexturePaths = {
        "../assets/UI_sprites/hot_bar/lich_of_flowers/basic.png",
        "../assets/UI_sprites/hot_bar/lich_of_flowers/wide.png",
        "../assets/UI_sprites/hot_bar/lich_of_flowers/offensive.png",
        "../assets/UI_sprites/hot_bar/lich_of_flowers/defensive.png"
    };
};

#endif // LICH_OF_FLOWERS_HOT_BAR_HPP