#include "MoveHandler.hpp"

void MoveHandler::registerCharacter(HandlerCharacter* characterRef) {
    character = characterRef;
}

void MoveHandler::registerPlayer(Player* playerRef) {
    player = playerRef;
}
