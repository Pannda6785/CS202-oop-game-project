#include "KeybindingConfigState.hpp"
#include "../GameStateManager.hpp"
#include "../../../audio/AudioManager.hpp"
#include "../../../input/InputInterpreterManager.hpp"

KeybindingConfigState::KeybindingConfigState(GameStateManager& gsm, BehindDots &behindDots, int indexPlayer)
    : gameStateManager(gsm), behindDots(behindDots), playerIndex(indexPlayer) {
    enter();
}

KeybindingConfigState::~KeybindingConfigState() {
    exit();
}

void KeybindingConfigState::enter() {
    keybindActions = {
        "MOVE RIGHT",
        "MOVE LEFT",
        "MOVE UP",
        "MOVE DOWN",
        "CONFIRM",
        "BACK",
        "PAUSE",
        "TOGGLE",
        "BASIC ATTACK",
        "WIDE ATTACK",
        "OFFENSIVE SKILL",
        "DEFENSIVE SKILL",
        "FOCUS MODE"
    };
    heading.setHasHeading(false);
    int buttonWidth = 700;
    int buttonHeight = 50;
    int buttonSpacing = 10;
    int buttonY = -30; // Centered vertically
    for(int i = 0; i < static_cast<int>(Unit::Input::InputCount); i++){
        Vector2 position = {GetScreenWidth() / 2 - buttonWidth / 2, buttonY += (buttonHeight + buttonSpacing)};
        keybindDisplays.push_back(std::make_unique<KeybindDisplay>(InputInterpreterManager::getInstance().getKeyMapping(playerIndex, static_cast<Unit::Input>(i))));
        keybindDisplays.back()->setPosition(position.x + buttonWidth - 100, position.y + buttonHeight / 2);
        keybindDisplays.back()->setLayer(20);
        auto button = std::make_unique<Button>(
            position.x,
            position.y,
            buttonWidth,
            buttonHeight,
            keybindActions[i],
            40,
            100,
            -1,
            "../assets/fonts/ferrum.otf",
            false
        );
        button->setLayer(10);
        button->setOnClickListener([this, i]() {
            AudioManager::getInstance().playSound("ClickButton");
            isWaitingForKeyPressed = true;
            pendingActionIndex = i;
        });
        button->setOnHoverEnterListener([this, i]() {
            AudioManager::getInstance().playSound("MenuCursor");
            keybindDisplays[i]->setHover(true);
        });
        button->setOnHoverExitListener([this, i]() {
            keybindDisplays[i]->setHover(false);
        });
        buttonManager.addButton(std::move(button));
    }
    // Return button
    std::unique_ptr<Button> returnButton = std::make_unique<Button>(
        GetScreenWidth() / 2 - buttonWidth / 2, 
        buttonY += buttonHeight + buttonSpacing,
        buttonWidth, 
        buttonHeight, 
        "RETURN", 
        40, 
        0, 
        0, // Center aligned
        "../assets/fonts/ferrum.otf",
        false
    );
    returnButton->setOnClickListener([this]() {
        AudioManager::getInstance().playSound("ClickButton");
        gameStateManager.popState();
    });
    returnButton->setOnHoverEnterListener([this]() {
        AudioManager::getInstance().playSound("MenuCursor");
    });
    buttonManager.addButton(std::move(returnButton));
}

void KeybindingConfigState::update(float dt) {
    if (isWaitingForKeyPressed) {
        // Check for key presses
        for (int key = KEY_SPACE; key <= KEY_KB_MENU; key++) {
            if (IsKeyPressed(key)) {
                isWaitingForKeyPressed = false;
                setInputKeyForAction(pendingActionIndex, key);
                pendingActionIndex = -1;
                return;
            }
        }
    }
    buttonManager.update(dt);
    behindDots.update(dt);
}

int KeybindingConfigState::waitForKeyPress() {
}

void KeybindingConfigState::setInputKeyForAction(int actionIndex, int raylibKey) {
    if (actionIndex >= 0 && actionIndex < keybindActions.size()) {
        InputInterpreterManager::getInstance().setKeyMapping(playerIndex, static_cast<Unit::Input>(actionIndex), raylibKey);
    }
    updateDisplay();
}

void KeybindingConfigState::updateDisplay() {
    // Update the display of keybindings
    for (size_t i = 0; i < keybindDisplays.size(); i++) {
        keybindDisplays[i]->setKey(InputInterpreterManager::getInstance().getKeyMapping(playerIndex, static_cast<Unit::Input>(i)));
    }
}

void KeybindingConfigState::exit() {
    // Clean up keybinding configuration UI elements
}

void KeybindingConfigState::setVisible(bool visible) {
    this->visible = visible;
}