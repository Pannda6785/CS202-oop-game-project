#include "LichOfFlowersHealthBar.hpp"

LichOfFlowersHealthBar::LichOfFlowersHealthBar(bool isLeftSide)
    : HealthBar(isLeftSide) {
    // Set character's signature color - vibrant green
    setSignatureColor({38,79,208,255});
    avatar.addTexture("../assets/UI_sprites/health_bar/lich_of_flowers_avatar.png");
    init();
}