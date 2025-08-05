#ifndef TEXTURE_BULLET_GRAPHICS_COMPONENT_HPP
#define TEXTURE_BULLET_GRAPHICS_COMPONENT_HPP

#include "BulletGraphicsComponent.hpp"

#include <vector>
#include <array>

class Texture;
class Bullet;

class TextureBulletGraphicsComponent : public BulletGraphicsComponent {
public:
    TextureBulletGraphicsComponent(const Texture* tex, float texResize);
    TextureBulletGraphicsComponent(std::vector<const Texture*> anim, int fps, float texResize);

    void addStartup(const Texture* startupTex, float startupTexResize);
    void addStartup(std::vector<const Texture*> startupAnim, int startupFps, float startupTexResize);

    void addFadein(float timeStart, float timeEnd); // when it ends
    void addFadeout(float timeStart, float timeEnd); // when it starts fading out

    void addBloom(float timeStart, float timeEnd);
    void addDebloom(float timeStart, float timeEnd);

    void addVelocityRotation(bool b); // defaults to false, when set texture will rotate towards the velocity direction
    void addRotation(float rps); // revolution per second
    void addFlip(bool horizontal, bool vertical);

    void addTint(std::array<int, 4> tint);

    void render() const override;
    void update(float dt) override;

private:
    // constant data
    std::vector<const Texture*> mainAnim; // 1 frames for static texture
    int mainFps;
    float mainTexResize;

    std::vector<const Texture*> startupAnim; // 1 frames for static texture
    int startupFps;
    float startupTexResize;

    float fadeinStart = 0.0f, fadeinEnd = 0;
    float fadeoutStart = 1e9, fadeoutEnd = 1e9;

    float bloomStart = 0, bloomEnd = 0;
    float debloomStart = 1e9, debloomEnd = 1e9;

    bool useVelocityMode = false;
    float rotationSpeed = 0.0f;
    bool flipH = false;
    bool flipV = false;

    std::array<int, 4> tint = {255, 255, 255, 255}; // RGBA

    // dynamic data
    float time = 0.0f;

};

#endif // ANIMATED_BULLET_GRAPHICS_COMPONENT_HPP