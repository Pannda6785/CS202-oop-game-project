#include "HeroOfFrostHealthBar.hpp"

HeroOfFrostHealthBar::HeroOfFrostHealthBar(bool isLeftSide)
    : HealthBar(isLeftSide) {
    // Set character's signature color - icy blue
    setSignatureColor({145,236,104,255});
    avatar.addTexture("../assets/UI_sprites/health_bar/hero_of_frost_avatar.png");
    init();
}