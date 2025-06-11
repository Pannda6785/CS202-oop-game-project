#include "raylib.h"

#include "Unit.hpp"

#include "graphics/GraphicsComponentManager.hpp"
#include "graphics/Renderer.hpp"

#include "input/InputInterpreter.hpp"
#include "input/KeyboardInputInterpreter.hpp"

#include "game/World.hpp"
#include "game/player/Player.hpp"
#include "game/character/CharacterGraphicsComponent.hpp"

#include <memory>
#include <vector>

int main() {
    const int screenWidth = 1440;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Maiden and Testing");

    SetTargetFPS(60);

    /*
        MAIN GAME LOOP
        + draw dt
        + update interpreters
        + update world
        + render
        + audio
    */

    std::unique_ptr<World> world = std::make_unique<World>();
    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();

    std::vector<std::shared_ptr<KeyboardInputInterpreter>> inputInterpreters = { std::make_shared<KeyboardInputInterpreter>(), std::make_shared<KeyboardInputInterpreter>() };
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveUp, KEY_W);
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveDown, KEY_S); 
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveLeft, KEY_A);
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveRight, KEY_D);

    std::unique_ptr<Player> player1 = std::make_unique<Player>(0, world.get());
    std::unique_ptr<Player> player2 = std::make_unique<Player>(1, world.get());

    player1->registerInputInterpreter(inputInterpreters[0]);
    player2->registerInputInterpreter(inputInterpreters[1]);
    player1->registerGraphicsComponent(std::make_unique<CharacterGraphicsComponent>(player1.get()));
    player2->registerGraphicsComponent(std::make_unique<CharacterGraphicsComponent>(player2.get()));

    world->addPlayer(std::move(player1));
    world->addPlayer(std::move(player2));

    world->init();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Maiden is Ball", 10, 10, 20, DARKGRAY);
        
        for (int i = 0; i < 2; i++)
        inputInterpreters[i]->update(dt); // Update input interpreters
        
        world->update(dt); // Update game world logic

        GraphicsComponentManager::instance().render(*renderer); // Update graphics components

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}