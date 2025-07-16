#include "raylib.h"

#include "Unit.hpp"

#include "graphics/GraphicsComponentManager.hpp"

#include "UI/button/ButtonManager.hpp"

#include <memory>
#include <vector>

#include <iostream>

#include "UI/game_state/GameStateManager.hpp"

#include "audio/AudioManager.hpp"

int main() {
    const int screenWidth = 1440;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Maiden and CS202");
    InitAudioDevice();

    SetTargetFPS(60);

    /*
        MAIN GAME LOOP
        + draw dt
        + update interpreters
        + update world
        + render
        + audio
    */

    GameStateManager gameStateManager;
    
    AudioManager::getInstance().init(); // Initialize audio manager


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Maiden and Hardcoded Background", 10, 10, 20, DARKGRAY);
        
        gameStateManager.processPendingStateChanges();

        gameStateManager.update(dt); // Update game state manager

        GraphicsComponentManager::instance().render(); // Update graphics components


        EndDrawing();
    }

    CloseWindow();

    return 0;
}