#ifndef DEPTH_SECRET_HOT_BAR_HPP
#define DEPTH_SECRET_HOT_BAR_HPP

#include "../HotBar.hpp"

class DepthSecretHotBar : public HotBar {
public:
    DepthSecretHotBar(bool isLeftSide = true);
    ~DepthSecretHotBar() = default;

private:
    const std::vector<std::string> abilityTexturePaths = {
        "../assets/UI_sprites/hot_bar/depth_secret/basic.png",
        "../assets/UI_sprites/hot_bar/depth_secret/wide.png",
        "../assets/UI_sprites/hot_bar/depth_secret/offensive.png",
        "../assets/UI_sprites/hot_bar/depth_secret/defensive.png"
    };
};

#endif // DEPTH_SECRET_HOT_BAR_HPP