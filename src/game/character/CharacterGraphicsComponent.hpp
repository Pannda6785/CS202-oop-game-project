#ifndef CHARACTER_GRAPHICS_COMPONENT_HPP
#define CHARACTER_GRAPHICS_COMPONENT_HPP

#include "../../Unit.hpp"
#include "../../graphics/GraphicsComponent.hpp"

#include <vector>
#include <string>
#include <unordered_map>

class Player;
class Texture;
class Shader;

class CharacterGraphicsComponent : public GraphicsComponent {
public:
    CharacterGraphicsComponent();
    virtual ~CharacterGraphicsComponent();

    void registerPlayer(Player* playerView);

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

};

#endif // CHARACTER_GRAPHICS_COMPONENT_HPP
