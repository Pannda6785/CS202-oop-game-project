#ifndef CHARACTER_GRAPHICS_COMPONENT_HPP
#define CHARACTER_GRAPHICS_COMPONENT_HPP

#include "../../Unit.hpp"
#include "../../graphics/GraphicsComponent.hpp"
#include "../player/IPlayerView.hpp"

#include <vector>

class Texture;

class CharacterGraphicsComponent : public GraphicsComponent {
public:
    CharacterGraphicsComponent(const IPlayerView* playerView);
    virtual ~CharacterGraphicsComponent(); // Destructor for cleanup

    void update(float dt);
    void render(Renderer& renderer) const;

    void takeHit();

protected:
    const IPlayerView* player;

    const float characterAnimationSpeed = 0.24f;
    std::vector<Texture*> idle;
    std::vector<Texture*> walkForward;
    std::vector<Texture*> walkBackward;
    std::vector<Texture*> stagger;
    std::vector<Texture*> wakeup;
    float frameTime;

    Texture* hitboxTexture;
    Texture* arrowTexture;

    void loadTextures(); // Load textures
    void unloadTextures(); // Unload textures
};

#endif // CHARACTER_GRAPHICS_COMPONENT_HPP
