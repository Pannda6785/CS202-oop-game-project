#include "SilentRedhoodHealthBar.hpp"

SilentRedhoodHealthBar::SilentRedhoodHealthBar(bool isLeftSide)
    : HealthBar(isLeftSide) {
    // Set character's signature color - rich crimson red
    setSignatureColor({203,49,59,255});
    avatar.addTexture("../assets/UI_sprites/health_bar/silent_redhood_avatar.png");
    init();
}