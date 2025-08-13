#include "DepthSecretHealthBar.hpp"

DepthSecretHealthBar::DepthSecretHealthBar(bool isLeftSide)
    : HealthBar(isLeftSide) {
    // Set character's signature color - deep teal
    setSignatureColor({41,211,159,255});
    avatar.addTexture("../assets/UI_sprites/health_bar/depth_secret_avatar.png");
    init();
}