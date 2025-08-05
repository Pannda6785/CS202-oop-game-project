#include "Character.hpp"

#include "../player/Player.hpp"
#include "../player/InputBufferer.hpp"

Character::Character(std::string name, float moveSpeed, float focusedSpeed, std::unique_ptr<CharacterGraphicsComponent> graphics)
    : name(std::move(name)), moveSpeed(moveSpeed), focusedSpeed(focusedSpeed), graphics(std::move(graphics)) {
}

void Character::registerPlayer(Player* playerRef) {
    player = playerRef;
    if (graphics) {
        graphics->registerPlayer(playerRef);
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
