#include "StormbeastHealthBar.hpp"

StormbeastHealthBar::StormbeastHealthBar(bool isLeftSide)
    : HealthBar(isLeftSide) {
    // Set character's signature color - storm blue
    setSignatureColor({151,126,233,255});
    avatar.addTexture("../assets/UI_sprites/health_bar/stormbeast_avatar.png");
    init();
}