#ifndef HOT_BAR_SLOT_HPP
#define HOT_BAR_SLOT_HPP

#include "../../../../UI/game_state/decorative_components/artwork/Artwork.hpp"
#include "../../../../UI/game_state/decorative_components/GameText.hpp"
#include <string>
#include <memory>

class HotBarSlot {
public:
    HotBarSlot();
    ~HotBarSlot();

    // Initialization
    void loadSkillIconSlotTexture(std::string texturePath);
    void setPosition(Vector2 pos);

    // State management
    void setCooldownDuration(float duration);
    void setFadeHidding(bool hidden);
    bool isOnCooldown() const;
    bool isHidden() const;
    float getWidth() const;
    Vector2 getPosition() const;

    // Update and render
    void update(float dt);

private:
    // UI Components
    Artwork skillIconSlot;  // The background slot
    GameText cooldownText;  // Text displaying cooldown

    // Cooldown management
    float cooldownDuration = 0.0f;

    // Transparency states
    bool fadeHidding = false;
    const float fadeHiddingAlpha = 0.1f;  // Transparency when hidden
    const float fadeCooldown = 0.5f;      // Transparency when on cooldown
    Vector2 pos = {0.0f, 0.0f};

    // Helper methods
    void updateCooldownText();
    void updateTransparency();
};

#endif // HOT_BAR_SLOT_HPP