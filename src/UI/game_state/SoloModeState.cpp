#include "SoloModeState.hpp"
#include "GameStateManager.hpp"
#include "MainMenuState.hpp"

SoloModeState::SoloModeState(GameStateManager& gsm)
    : gameStateManager(gsm)
{
    inputInterpreters = { std::make_shared<KeyboardInputInterpreter>(), std::make_shared<KeyboardInputInterpreter>() };
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveUp, KEY_W);
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveDown, KEY_S);
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveLeft, KEY_A);
    inputInterpreters[1]->setKeyMapping(Unit::Input::MoveRight, KEY_D);

    inputInterpreters[1]->setKeyMapping(Unit::Input::Basic, KEY_ONE);
    inputInterpreters[1]->setKeyMapping(Unit::Input::Wide, KEY_TWO); 
    inputInterpreters[1]->setKeyMapping(Unit::Input::Offensive, KEY_THREE);
    inputInterpreters[1]->setKeyMapping(Unit::Input::Defensive, KEY_FOUR);

    world = std::make_unique<World>();

    std::unique_ptr<Player> player1 = std::make_unique<Player>(0, world.get(), world.get(), std::make_unique<DemoCharacter>(), inputInterpreters[0]);
    std::unique_ptr<Player> player2 = std::make_unique<Player>(1, world.get(), world.get(), std::make_unique<DemoCharacter>(), inputInterpreters[1]);

    world->addPlayer(std::move(player1));
    world->addPlayer(std::move(player2));

    world->init();

    enter();
}

SoloModeState::~SoloModeState() = default;

void SoloModeState::enter() {
    std::unique_ptr<Button> backButton = std::make_unique<Button>(
        50, 50, 200, 50, "Back to Main Menu"
    );
    backButton->setOnClickListener([&gsm = gameStateManager]() {
        std::cout << "Returning to Main Menu..." << std::endl;
        gsm.changeState(std::make_unique<MainMenuState>(gsm));
    });
    backButton->setOnHoverEnterListener([]() {
        std::cout << "Hovered over Back button!" << std::endl;
    });
    buttonManager.addButton(std::move(backButton));
}

void SoloModeState::update(float dt) {
    // Update input interpreters and world if needed
    for (size_t i = 0; i < inputInterpreters.size(); i++)
        inputInterpreters[i]->update(dt);
    world->update(dt);

    buttonManager.update(dt);
}

void SoloModeState::exit() {
}