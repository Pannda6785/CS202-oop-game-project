#ifndef WORLD_CAMERA_HPP
#define WORLD_CAMERA_HPP

#include "../IWorldView.hpp"

class Camera2D;

class WorldCamera {
    static constexpr float SHAKE_DURATION = 0.5f;  // seconds
    
public:
    WorldCamera(const IWorldView* world);
    ~WorldCamera();

    void update(float dt);

    // trigger a camera shake
    void shake();

private:

    const IWorldView* world;
    Camera2D* camera;

    float deadZoneWidth;
    float deadZoneHeight;

    // shake state
    float shakeTimer = 0.0f;

    void followPlayers(float dt);
    void clampToBattlefield();
    void applyShake();
};

#endif // WORLD_CAMERA_HPP
