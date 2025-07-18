#ifndef BEHIND_DOTS_GRAPHICS_COMPONENT_HPP
#define BEHIND_DOTS_GRAPHICS_COMPONENT_HPP
#include "../../../graphics/GraphicsComponent.hpp"
#include <raylib.h>
#include <vector>

class BehindDotsGraphicsComponent : public GraphicsComponent {
public:
    BehindDotsGraphicsComponent();
    ~BehindDotsGraphicsComponent() override;

    void init(const Texture *_dotTexture, const Vector2& _position, float _scale, const Vector2& _offset, float _lifeTime, Color _color = {255, 255, 255, 255});
    void update(float dt, Color color);
    void render() const override;
    bool exist() const;
public:
    const Texture *dotTexture = nullptr; // Pointer to the dot texture
    bool loadedDotTexture = false; // Flag to check if the texture is loaded
    float scale;
    Vector2 position;
    Vector2 offset;
    Color color;
    float lifeTime;
    float timer[2];
    
};

#endif // BEHIND_DOTS_GRAPHICS_COMPONENT_HPP