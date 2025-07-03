#include "Character.hpp"

#include "../player/IPlayerControl.hpp"
#include "../player/InputBufferer.hpp"
#include "../player/IPlayerView.hpp"

Character::Character(std::string name, float moveSpeed, float focusedSpeed, std::unique_ptr<CharacterGraphicsComponent> graphics)
    : name(std::move(name)), moveSpeed(moveSpeed), focusedSpeed(focusedSpeed), graphics(std::move(graphics)) {
}

void Character::registerPlayer(IPlayerControl* playerRef) {
    player = playerRef;
    if (graphics) {
        IPlayerView* view = dynamic_cast<IPlayerView*>(player);
        if (view) {
            graphics->registerPlayer(view);
        } else {
            throw std::runtime_error("Character::registerPlayer - Player passed does not implement IPlayerView interface");
        }
    }
}

void Character::init() {
    graphics->init();
}

std::string Character::getName() const {
    return name;
}

float Character::getMoveSpeed() const {
    return moveSpeed;
}

float Character::getFocusedSpeed() const {
    return focusedSpeed;
}

CharacterGraphicsComponent* Character::getGraphics() {
    return graphics.get();
}
