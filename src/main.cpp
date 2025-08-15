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

#include "UI/game_state/decorative_components/Artwork.hpp"
#include "UI/game_state/decorative_components/MovingText.hpp"
#include "UI/game_state/decorative_components/MovingTextTile.hpp"

#include "UI/game_state/versus_mode_state/HUD/hot_bar/HotBar.hpp"
#include "UI/game_state/versus_mode_state/HUD/hot_bar/HotBarSlot.hpp"
#include "UI/game_state/versus_mode_state/HUD/hot_bar/sun_priestess_hot_bar/SunPriestessHotBar.hpp"

#include "UI/game_state/versus_mode_state/HUD/health_bar/HealthBar.hpp"
#include "UI/game_state/versus_mode_state/ribbon_effect/MovingTextTileManager.hpp"

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
    AudioManager::getInstance().setMasterVolume(0.5f);
    AudioManager::getInstance().stopThemeMusic();
    if(!tool) CustomCursor::getInstance().init(); // Initialize custom cursor

    Vector2 initialPoint = { -1, -1 };
    Vector2 endPoint = { -1, -1 };
    bool measuring = false;

    // // // Create a moving text tile for character name
    // MovingTextTile characterNameTile;

    // // Set up the tile part
    // characterNameTile.setTileTexture("../assets/UI_sprites/charselect_ribbon_mid.png");
    // characterNameTile.setTileStartPosition({0, 600});
    // characterNameTile.setTileAngle(110.0f);
    // characterNameTile.setTileSpeed(75.0f);
    // characterNameTile.setTileScale(0.75f);
    // characterNameTile.setTileInitialNum(15);
    // characterNameTile.setTileRestrictArea({-50.0f, -50.0f, GetScreenWidth() + 100.0f, GetScreenHeight() + 100.0f});

    // // Set up the background part
    // characterNameTile.setBackgroundColor(WHITE);
    // characterNameTile.setBackgroundWidthRatio(0.8f);  // Make background a bit wider than the tile

    // // Set up the text part
    // characterNameTile.setText("PAUSE");
    // characterNameTile.setTextFont("../assets/fonts/ferrum.otf");
    // characterNameTile.setTextFontSize(120);
    // characterNameTile.setTextColor(BLACK);
    // characterNameTile.setTextSpacing(200.0f);

    // // Initialize the composite component
    // characterNameTile.setLayer(100);  // Set base layer
    // // characterNameTile.setTileExpandingTime(2.0f);
    // // characterNameTile.setTileStartExpand(true);
    // characterNameTile.init();

    // Background background;
    // background.setBackgroundColor(WHITE);
    // background.setBackgroundRect({0, 700, GetScreenWidth(), GetScreenHeight()});
    // background.setLayer(50);
    // GameText gameText;
    // gameText.loadFont("../assets/fonts/ferrum2.otf");
    // gameText.setText("PAUSE");
    // gameText.setPosition(0, (700 + GetScreenHeight()) / 2);
    // gameText.setColor(BLACK);
    // gameText.setOriginRatio({0.0f, 0.435f});
    // gameText.setFontSize(245);
    // gameText.setLayer(100);

    // MovingTextTileManager ribbonManager;
    // ribbonManager.addPause();

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

        // characterNameTile.update(dt);

        // ribbonManager.update(dt);

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