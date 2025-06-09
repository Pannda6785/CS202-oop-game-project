#include "raylib.h"

#include "GameUnits.h"

#include "Renderer.h"

#include "IWorldView.h"
#include "World.h"

#include "InputInterpreter.h"
#include "KeyboardInputInterpreter.h"

#include "Player.h"
#include "DemoCharacter.h"

#include <memory>
#include <vector>

int main() {
    const int screenWidth = 1440;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Maiden and Testing");

    SetTargetFPS(60);

    std::unique_ptr<World> world = std::make_unique<World>();
    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(world.get());

    std::vector<std::shared_ptr<KeyboardInputInterpreter>> inputInterpreters = { std::make_shared<KeyboardInputInterpreter>(0), std::make_shared<KeyboardInputInterpreter>(1) };

    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveUp, KEY_W);
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveDown, KEY_S); 
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveLeft, KEY_A);
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveRight, KEY_D);

    std::unique_ptr<Player> player1 = std::make_unique<Player>(0, std::make_unique<DemoCharacter>(), inputInterpreters[0], world.get(), world.get());
    std::unique_ptr<Player> player2 = std::make_unique<Player>(1, std::make_unique<DemoCharacter>(), inputInterpreters[1], world.get(), world.get());

    world->addPlayer(std::move(player1));
    world->addPlayer(std::move(player2));
    
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Maiden is Ball", 10, 10, 20, DARKGRAY);
        
        for (int i = 0; i < 2; i++)
        inputInterpreters[i]->update(dt); // Update input interpreters
        
        world->update(dt); // Update game world logic
        
        renderer->renderBattle(); // Render game world
        renderer->renderHUD(); // Render HUD

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}