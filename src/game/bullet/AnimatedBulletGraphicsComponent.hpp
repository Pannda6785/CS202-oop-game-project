#ifndef ANIMATED_BULLET_GRAPHICS_COMPONENT_HPP
#define ANIMATED_BULLET_GRAPHICS_COMPONENT_HPP

#include "BulletGraphicsComponent.hpp"

#include <vector>

class Texture;
class Bullet;

class AnimatedBulletGraphicsComponent : public BulletGraphicsComponent {
public:
    AnimatedBulletGraphicsComponent(const Bullet* bullet, std::vector<const Texture*> anim, int fps, float texResize);

    void addStartup(float startupGradient, std::vector<const Texture*> startupAnim = {}, int startupFps = 8, float startupTexResize = 1.0f);
    void addFlip(bool horizontal, bool vertical);
    void addRotation(float rps); // rps: revolution per second, negative for clockwise
    void addOpacity(float opacity);

    void render() const override;
    void update(float dt) override;

private:
    std::vector<const Texture*> mainAnim;
    int mainFps;
    float mainTexResize;
    bool flipH = false;
    bool flipV = false;
    float rotationSpeed = 0.0f;

    std::vector<const Texture*> startupAnim;
    int startupFps;
    float startupTexResize;
    float startupGradient = 0.05f;
    float opacityScale = 1.0f;

    float timer = 0.0f;

};

#endif // ANIMATED_BULLET_GRAPHICS_COMPONENT_HPP