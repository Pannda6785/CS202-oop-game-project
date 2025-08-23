#include "RoyalArcanistHealthBar.hpp"

RoyalArcanistHealthBar::RoyalArcanistHealthBar(bool isLeftSide)
    : HealthBar(isLeftSide) {
    // Set character's signature color - royal purple
    setSignatureColor({65,66,68,255});
    avatar.addTexture("../assets/UI_sprites/health_bar/royal_arcanist_avatar.png");
    init();
}