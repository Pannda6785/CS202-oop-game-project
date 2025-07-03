#include "MoveHandler.hpp"

void MoveHandler::registerCharacter(HandlerCharacter* characterRef) {
    character = characterRef;
}

void MoveHandler::registerPlayer(IPlayerControl* playerRef) {
    player = playerRef;
}
