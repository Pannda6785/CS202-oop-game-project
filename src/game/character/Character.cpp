#include "Character.hpp"

#include "../player/IPlayerControl.hpp"
#include "../player/InputBufferer.hpp"

std::string Character::getName() {
    return name;
}

float Character::getMoveSpeed() {
    return moveSpeed;
}

float Character::getFocusedSpeed() {
    return focusedSpeed;
}

void Character::registerPlayer(IPlayerControl* playerRef) {
    player = playerRef;
}

CharacterGraphicsComponent* Character::getGraphics() {
    return graphics.get();
}
