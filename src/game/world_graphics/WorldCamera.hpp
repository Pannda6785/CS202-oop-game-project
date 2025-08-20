#ifndef WORLD_CAMERA_HPP
#define WORLD_CAMERA_HPP

#include "../IWorldView.hpp"

class Camera2D;

class WorldCamera {
public:
    WorldCamera(const IWorldView* world);
    ~WorldCamera();

    void update(float dt);

private:
    const IWorldView* world;
    Camera2D* camera;
    
    float deadZoneWidth;
    float deadZoneHeight;

    void followPlayers(float dt);
    void clampToBattlefield();
};

#endif // WORLD_CAMERA_HPP
