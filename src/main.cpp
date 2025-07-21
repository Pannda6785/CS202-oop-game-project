#include "raylib.h"

#include "Unit.hpp"

#include "graphics/GraphicsComponentManager.hpp"

#include "UI/button/ButtonManager.hpp"

#include <memory>
#include <vector>

#include <iostream>

#include "UI/game_state/GameStateManager.hpp"

#include "audio/AudioManager.hpp"
#include "UI/custom_cursor/CustomCursor.hpp"

int main() {
    const int screenWidth = 1440;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Maiden and CS202");
    InitAudioDevice();

    SetTargetFPS(200);

    /*
        MAIN GAME LOOP
        + draw dt
        + update interpreters
        + update world
        + render
        + audio
    */

    HideCursor(); // Hide the default cursor

    GameStateManager gameStateManager;
    
    
    AudioManager::getInstance().init(); // Initialize audio manager
    CustomCursor::getInstance().init(); // Initialize custom cursor

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(BLACK);

        gameStateManager.processPendingStateChanges();

        gameStateManager.update(dt); // Update game state manager
        CustomCursor::getInstance().update(dt); // Update custom cursor

        GraphicsComponentManager::instance().render(); // Update graphics components


        EndDrawing();
    }

    CloseWindow();

    return 0;
}