#include "SunPriestessHealthBar.hpp"

SunPriestessHealthBar::SunPriestessHealthBar(bool isLeftSide)
    : HealthBar(isLeftSide) {
    // Set character's signature color
    setSignatureColor({235,115,60,255}); // Sun Priestess orange color
    avatar.addTexture("../assets/UI_sprites/health_bar/sun_priestess_avatar.png");
    init();
}