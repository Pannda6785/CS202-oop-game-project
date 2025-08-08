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

#include "UI/game_state/versus_mode_state/combat_feedback/CombatFeedback.hpp"

#include <algorithm>
#include <iostream>

#include "UI/game_state/versus_mode_state/combat_feedback/CombatFeedbackManager.hpp"

int main() {
    const int screenWidth = 1440;
    const int screenHeight = 900;

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

    bool tool = true;

    if(!tool) HideCursor(); // Hide the default cursor

    GameStateManager gameStateManager;
    
    AudioManager::getInstance().init(); // Initialize audio manager
    AudioManager::getInstance().loadThemeMusic("../assets/audio/music_mainthema.ogg");
    if(!tool) CustomCursor::getInstance().init(); // Initialize custom cursor

    Vector2 initialPoint = { -1, -1 };
    Vector2 endPoint = { -1, -1 };
    bool measuring = false;

    // CombatFeedbackManager combatFeedbackManager;
    // bool added = false;

    // Texture2D tmp;
    // bool addTmp = false;

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

        // if(IsKeyPressed(KEY_ESCAPE)){
        //     gameStateManager.popState();
        // }

        // if(!added){
        //     combatFeedbackManager.addHitEffect({0, 0}, {0, 0});
        //     added = true;
        // }

        // if(!addTmp){
        //     tmp = LoadTexture("../assets/UI_sprites/spr_splatter_0.png");
        //     addTmp = true;
        // }
        // bool isLeft = true;
        // bool isUp = false;
        // Rectangle sourceRec = {0, 0, static_cast<float>(tmp.width), static_cast<float>(tmp.height) };
        // float scale = 0.7f;
        // Vector2 originRatio = {0.75, 0.83};
        // if(!isLeft) {
        //     sourceRec.width = -static_cast<float>(tmp.width);
        //     originRatio.x = 1.0f - originRatio.x;
        // }
        // if(!isUp) {
        //     sourceRec.height = -static_cast<float>(tmp.height);
        //     originRatio.y = 1.0f - originRatio.y;
        // }
        // Vector2 pos = {200.0f, 200.0f};
        // Rectangle destRec = { pos.x, pos.y, scale * static_cast<float>(tmp.width), scale * static_cast<float>(tmp.height)};
        // Vector2 origin = { originRatio.x * tmp.width * scale, originRatio.y * tmp.height * scale };
        // DrawTexturePro(tmp, sourceRec, destRec, origin, 0.0f, WHITE);
        // DrawRectangle(pos.x, pos.y, 5.0f, 5.0f, WHITE); // Draw a semi-transparent overlay
        // // destRec = { 100.0f, 100.0f, static_cast<float>(tmp.width), static_cast<float>(tmp.height)};
        // // origin = { 100.0f, 100.0f };
        // // DrawTexturePro(tmp, sourceRec, destRec, origin, 0.0f, WHITE);

        gameStateManager.processPendingStateChanges();

        gameStateManager.update(dt); // Update game state manager

        // combatFeedbackManager.update(dt); // Update combat feedback manager


        if(!tool) CustomCursor::getInstance().update(dt); // Update custom cursor

        if(gameStateManager.isEmpty()) {
            std::cerr << "GameStateManager is empty! Exiting..." << std::endl;
            break; // Exit if no game state is present
        }

        GraphicsComponentManager::instance().render(); // Update graphics components

        

        EndDrawing();
    }

    // if(addTmp) {
    //     UnloadTexture(tmp); // Unload temporary texture
    // }   

    CloseWindow();

    return 0;
}