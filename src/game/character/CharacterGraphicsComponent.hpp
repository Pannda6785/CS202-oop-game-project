#ifndef CHARACTER_GRAPHICS_COMPONENT_HPP
#define CHARACTER_GRAPHICS_COMPONENT_HPP

#include "../../Unit.hpp"
#include "../../graphics/GraphicsComponent.hpp"

#include <vector>
#include <string>

class IPlayerView;
class Texture;
class Shader;

class CharacterGraphicsComponent : public GraphicsComponent {
public:
    CharacterGraphicsComponent(const IPlayerView* playerView);
    virtual ~CharacterGraphicsComponent();

    void render() const override;
    void update(float dt);

    // Event based
    void resize(float scale);
    void takeHit(float staggerTime);

protected:
    virtual void loadTextures() {};
    virtual void unloadTextures() {};
    virtual bool characterSpecificUpdate(float dt) { return false; };

    void renderUnderlay() const; // magic circle, ring, arrow
    void renderOverlay() const; // hitbox
    void renderCharacter() const; // character and all that animations

protected:
    const IPlayerView* player;
    
    const Texture* toRenderCharacterTexture = nullptr;
    const float animationFPS = 5.0f; // 5 frames per second
    float time = 0;
    float timeBuffer = 0;
    int curAnimId = 0;
    float size = 1;

    std::vector<Texture*> idleAnim;
    std::vector<Texture*> walkAnim;
    std::vector<Texture*> backAnim;
    std::vector<Texture*> staggerAnim;
    std::vector<Texture*> wakeAnim;

    Texture* hitboxTexture;
    Texture* arrowTexture;

private:
    const float flashFrequency = 5;
    float remainingStaggerTime = 0.0f;
    int wakeAnimId0 = 0;

    Shader* whiteSilhouette = nullptr;
};

#endif // CHARACTER_GRAPHICS_COMPONENT_HPP
