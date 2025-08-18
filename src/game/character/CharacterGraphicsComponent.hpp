#ifndef CHARACTER_GRAPHICS_COMPONENT_HPP
#define CHARACTER_GRAPHICS_COMPONENT_HPP

#include "../../Unit.hpp"
#include "../../graphics/GraphicsComponent.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <array>

class Player;
class Texture;
class Shader;

class CharacterGraphicsComponent : public GraphicsComponent {
    static constexpr float CHARACTER_HEIGHT = 112;

    static constexpr float HITBOX_RADIUS_RATIO = 5;
    static constexpr float MAGIC_CIRCLE_RADIUS = 75;
    static constexpr float OUTER_RING_RADIUS = 260;
    static constexpr float INNER_RING_RADIUS = 210;
    static constexpr float ARROW_RADIUS = 75;
    static constexpr float MIN_OPACITY = 0.65f;
    static constexpr float TRANSITION_SPEED = 0.1f; // how fast the ring transitions when focused
    
    static constexpr float RPS = 1 / 2.5f;
    static constexpr float FLASH_FREQUENCY = 4.0f;

public:
    CharacterGraphicsComponent();
    virtual ~CharacterGraphicsComponent();

    void registerPlayer(Player* playerView);
    std::array<int, 4> getSignatureColor() const;

    void render() const override final;
    void init();
    void update(float dt);

    // Event based
    void resize(float scale);
    float getSize() const { return size; }
    void takeHit(float staggerTime);

protected:
    virtual void loadTextures() = 0;
    virtual void unloadTextures() = 0;
    virtual bool characterSpecificUpdate(float dt) { return false; };
    void playAnim(const std::string& animName, bool restart = false);
    bool animFinished() const;

private:
    void renderUnderlay() const; // magic circle, ring, arrow
    void renderOverlay() const; // hitbox
    void renderCharacter() const; // character and all that animations

protected:
    const Player* player;
    std::array<int, 4> signatureColor = {255, 255, 255, 255}; // default white

    struct Animation {
        std::vector<const Texture*> frames;
        float fps;
        bool loop;
        Animation() = default;
        Animation(std::vector<const Texture*> frames, float fps, bool loop)
            : frames(std::move(frames)), fps(fps), loop(loop) {}
    };
    std::unordered_map<std::string, Animation> animations;
    std::string currentAnimName;
    
private:
    const Texture* toRenderCharacterTexture = nullptr;
    
    float time = 0;
    float animStartTime = 0;

    float size = 1;

    Shader* whiteSilhouette = nullptr;

    float remainingStaggerTime = 0.0f;
    float remainingWakeUpTime = 0.0f;

    float currentRingRadius = OUTER_RING_RADIUS;
    float currentOpacity = MIN_OPACITY;

};

#endif // CHARACTER_GRAPHICS_COMPONENT_HPP
