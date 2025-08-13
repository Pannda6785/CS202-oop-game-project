#include "DreadwyrmHeirHealthBar.hpp"

DreadwyrmHeirHealthBar::DreadwyrmHeirHealthBar(bool isLeftSide)
    : HealthBar(isLeftSide) {
    // Set character's signature color - dragon red
    setSignatureColor({235,219,152,255});
    avatar.addTexture("../assets/UI_sprites/health_bar/dreadwyrm_heir_avatar.png");
    init();
}