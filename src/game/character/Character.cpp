#include "Character.hpp"

#include "../IBulletSpawner.hpp"
#include "../player/IPlayerControl.hpp"
#include "../player/InputBufferer.hpp"

Character::Character(IBulletSpawner* bulletSpawnerRef)
    : bulletSpawner(bulletSpawnerRef) {}

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

void Character::registerInputBufferer(InputBufferer* inputRef) {
    input = inputRef;
}
