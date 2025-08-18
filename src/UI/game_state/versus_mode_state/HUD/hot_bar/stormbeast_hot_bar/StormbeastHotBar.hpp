#ifndef STORMBEAST_HOT_BAR_HPP
#define STORMBEAST_HOT_BAR_HPP

#include "../HotBar.hpp"

class StormbeastHotBar : public HotBar {
public:
    StormbeastHotBar(bool isLeftSide = true);
    ~StormbeastHotBar() = default;

private:
    const std::vector<std::string> abilityTexturePaths = {
        "../assets/UI_sprites/hot_bar/stormbeast/basic.png",
        "../assets/UI_sprites/hot_bar/stormbeast/wide.png",
        "../assets/UI_sprites/hot_bar/stormbeast/offensive.png",
        "../assets/UI_sprites/hot_bar/stormbeast/defensive.png"
    };
};

#endif // STORMBEAST_HOT_BAR_HPP