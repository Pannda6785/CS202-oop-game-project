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
    SetExitKey(KEY_NULL);


    /*
        MAIN GAME LOOP
        + draw dt
        + update interpreters
        + update world
        + render
        + audio
    */

    bool tool = true;

    if(!tool) HideCursor(); // Hide the default cursor

    GameStateManager gameStateManager;
    
    AudioManager::getInstance().init(); // Initialize audio manager
    AudioManager::getInstance().loadThemeMusic("../assets/audio/music_mainthema.ogg");
    if(!tool) CustomCursor::getInstance().init(); // Initialize custom cursor

    Vector2 initialPoint = { -1, -1 };
    Vector2 endPoint = { -1, -1 };
    bool measuring = false;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(BLACK);

        if(tool){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                initialPoint = GetMousePosition();
                measuring = true;
                endPoint = { -1, -1 };
            }

            // Mouse release: end measuring
            if (measuring && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                endPoint = GetMousePosition();
                measuring = false;

                // Measure pixel difference
                std::cout << "Initial point: (" 
                        << initialPoint.x << ", " << initialPoint.y << "), "
                        << "End point: (" 
                        << endPoint.x << ", " << endPoint.y << ")" << std::endl;
                std::cout << "Pixel difference: "
                        << "X: " << endPoint.x - initialPoint.x
                        << ", Y: " << endPoint.y - initialPoint.y
                        << std::endl;
                initialPoint = { -1, -1 }; // Reset initial point
                endPoint = { -1, -1 }; // Reset end point
            }
        }

        if(IsKeyPressed(KEY_ESCAPE)){
            gameStateManager.popState();
        }

        gameStateManager.processPendingStateChanges();
        AudioManager::getInstance().update(dt);

        gameStateManager.update(dt); // Update game state manager
        if(!tool) CustomCursor::getInstance().update(dt); // Update custom cursor

        if(gameStateManager.isEmpty()) {
            std::cerr << "GameStateManager is empty! Exiting..." << std::endl;
            break; // Exit if no game state is present
        }

        GraphicsComponentManager::instance().render(); // Update graphics components

        EndDrawing();
    }

    CloseWindow();

    return 0;
}