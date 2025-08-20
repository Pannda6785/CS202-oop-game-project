#include "WorldCamera.hpp"

#include "../../Unit.hpp"
#include "../../graphics/GraphicsComponentManager.hpp"
#include "../player/Player.hpp"

#include <algorithm>
#include <raylib.h>

WorldCamera::WorldCamera(const IWorldView* world)
    : world(world)
{
    camera = new Camera2D();
    camera->zoom = 1.0f;
    camera->rotation = 0.0f;
    camera->offset = {
        GraphicsComponentManager::NATIVE_WIDTH  / 2.0f,
        GraphicsComponentManager::NATIVE_HEIGHT / 2.0f
    };
    camera->target = {
        Unit::BATTLEFIELD_WIDTH  / 2.0f,
        Unit::BATTLEFIELD_HEIGHT / 2.0f
    };

    deadZoneWidth  = GraphicsComponentManager::NATIVE_WIDTH  / 3.0f;
    deadZoneHeight = GraphicsComponentManager::NATIVE_HEIGHT / 3.0f;

    GraphicsComponentManager::instance().addTaggedCamera(*camera, "world_object");
}

WorldCamera::~WorldCamera() {
    // unregister before deleting
    GraphicsComponentManager::instance().removeTaggedCamera("world_object");
    delete camera;
}

void WorldCamera::update(float dt) {
    followPlayers(dt);
    clampToBattlefield();

    // refresh tagged camera each frame
    GraphicsComponentManager::instance().addTaggedCamera(*camera, "world_object");
}

void WorldCamera::followPlayers(float dt) {
    auto players = world->getPlayers();
    if (players.empty()) return;

    // average player position
    Unit::Vec2D avgPos(0.0f, 0.0f);
    for (auto* p : players) {
        avgPos += p->getPosition();
    }
    avgPos /= players.size();

    // dead zone bounds
    float left   = camera->target.x - deadZoneWidth  / 2.0f;
    float right  = camera->target.x + deadZoneWidth  / 2.0f;
    float top    = camera->target.y - deadZoneHeight / 2.0f;
    float bottom = camera->target.y + deadZoneHeight / 2.0f;

    // adjust only if avgPos outside dead zone
    if (avgPos.x < left)       camera->target.x = avgPos.x + deadZoneWidth  / 2.0f;
    else if (avgPos.x > right) camera->target.x = avgPos.x - deadZoneWidth  / 2.0f;

    if (avgPos.y < top)        camera->target.y = avgPos.y + deadZoneHeight / 2.0f;
    else if (avgPos.y > bottom)camera->target.y = avgPos.y - deadZoneHeight / 2.0f;
}

void WorldCamera::clampToBattlefield() {
    float halfW = GraphicsComponentManager::NATIVE_WIDTH  / 2.0f;
    float halfH = GraphicsComponentManager::NATIVE_HEIGHT / 2.0f;

    float minX = halfW;
    float maxX = Unit::BATTLEFIELD_WIDTH  - halfW;
    float minY = halfH;
    float maxY = Unit::BATTLEFIELD_HEIGHT - halfH;

    camera->target.x = std::clamp(camera->target.x, minX, maxX);
    camera->target.y = std::clamp(camera->target.y, minY, maxY);
}
