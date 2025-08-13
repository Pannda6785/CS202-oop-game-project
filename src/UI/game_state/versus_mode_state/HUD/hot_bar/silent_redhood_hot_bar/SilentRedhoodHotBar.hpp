#ifndef SILENT_REDHOOD_HOT_BAR_HPP
#define SILENT_REDHOOD_HOT_BAR_HPP

#include "../HotBar.hpp"

class SilentRedhoodHotBar : public HotBar {
public:
    SilentRedhoodHotBar(bool isLeftSide = true);
    ~SilentRedhoodHotBar() = default;

private:
    const std::vector<std::string> abilityTexturePaths = {
        "../assets/UI_sprites/hot_bar/silent_redhood/basic.png",
        "../assets/UI_sprites/hot_bar/silent_redhood/wide.png",
        "../assets/UI_sprites/hot_bar/silent_redhood/offensive.png",
        "../assets/UI_sprites/hot_bar/silent_redhood/defensive.png"
    };
};

#endif // SILENT_REDHOOD_HOT_BAR_HPP