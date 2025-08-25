#include "raylib.h"

#include "graphics/GraphicsComponentManager.hpp"
#include "UI/game_state/GameStateManager.hpp"
#include "audio/AudioManager.hpp"
#include "UI/custom_cursor/CustomCursor.hpp"

#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    const int screenWidth = GraphicsComponentManager::instance().getWindowWidth();
    const int screenHeight = GraphicsComponentManager::instance().getWindowHeight();

    InitWindow(screenWidth, screenHeight, "Maiden and CS202");
    InitAudioDevice();

    SetTargetFPS(120);
    SetExitKey(KEY_NULL);

    /*
        MAIN GAME LOOP
        + draw dt
        + update interpreters
        + update world
        + render
        + audio
    */

    bool tool = false;

    if(!tool) HideCursor(); // Hide the default cursor

    GameStateManager gameStateManager;
    
    AudioManager::getInstance().init(); // Initialize audio manager
    AudioManager::getInstance().loadThemeMusic("../assets/audio/music_mainthema.ogg");
    AudioManager::getInstance().setMasterVolume(0.5f);
    AudioManager::getInstance().stopThemeMusic();
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

        gameStateManager.processPendingStateChanges();
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