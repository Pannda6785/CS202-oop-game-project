#include "raylib.h"

#include "Unit.hpp"

#include "graphics/GraphicsComponentManager.hpp"

#include "input/InputInterpreter.hpp"
#include "input/KeyboardInputInterpreter.hpp"

#include "game/World.hpp"
#include "game/player/Player.hpp"

#include "game/character/bin/DemoCharacter.hpp"
#include "game/character/priestess/Priestess.hpp"

#include <memory>
#include <vector>

int main() {
    const int screenWidth = 1440;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Maiden and CS202");

    SetTargetFPS(60);

    /*
        MAIN GAME LOOP
        + draw dt
        + update interpreters
        + update world
        + render
        + audio
    */

    std::vector<std::shared_ptr<KeyboardInputInterpreter>> inputInterpreters = { std::make_shared<KeyboardInputInterpreter>(), std::make_shared<KeyboardInputInterpreter>() };
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveUp, KEY_W);
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveDown, KEY_S); 
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveLeft, KEY_A);
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveRight, KEY_D);

    inputInterpreters[1]->setKeyMapping(Unit::Input::Basic, KEY_ONE);
    inputInterpreters[1]->setKeyMapping(Unit::Input::Wide, KEY_TWO); 
    inputInterpreters[1]->setKeyMapping(Unit::Input::Offensive, KEY_THREE);
    inputInterpreters[1]->setKeyMapping(Unit::Input::Defensive, KEY_FOUR);

    std::unique_ptr<World> world = std::make_unique<World>();

    std::unique_ptr<Player> player1 = std::make_unique<Player>(0, world.get(), world.get(), std::make_unique<Priestess>(), inputInterpreters[0]);
    std::unique_ptr<Player> player2 = std::make_unique<Player>(1, world.get(), world.get(), std::make_unique<DemoCharacter>(), inputInterpreters[1]);

    world->addPlayer(std::move(player1));
    world->addPlayer(std::move(player2));

    world->init();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Maiden and Hardcoded Background", 10, 10, 20, DARKGRAY);
        
        for (int i = 0; i < 2; i++)
        inputInterpreters[i]->update(dt); // Update input interpreters
        
        world->update(dt); // Update game world logic

        GraphicsComponentManager::instance().render(); // Update graphics components

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}