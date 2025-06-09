#ifndef RENDERER_H
#define RENDERER_H

#include "IWorldView.h"
#include "raylib.h"

class Renderer {
public:
    Renderer(IWorldView* world) : world(world) {}

    void renderBattle();
    void renderHUD();

    // More sandboxing rendering tools for players and bullets to draw themselves 

private:
    IWorldView* world;
};

#endif // RENDERER_H
