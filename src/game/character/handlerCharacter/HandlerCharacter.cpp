#include "HandlerCharacter.hpp"

#include "MoveHandler.hpp"
#include "../../player/Player.hpp"
#include "../../player/InputBufferer.hpp"

HandlerCharacter::HandlerCharacter(std::string name, float moveSpeed, float focusedSpeed, std::unique_ptr<CharacterGraphicsComponent> graphics)
    : Character(std::move(name), moveSpeed, focusedSpeed, std::move(graphics)) {
    fill(moveHandlers.begin(), moveHandlers.end(), nullptr);
    order = {};
}

void HandlerCharacter::registerPlayer(Player* playerRef) {
    Character::registerPlayer(playerRef);
    for (auto& handler : moveHandlers) {
        if (handler) {
            handler->registerCharacter(this);
            handler->registerPlayer(playerRef);
        } else {
            std::cerr << "Warning: MoveHandler is not initialized for character " << name << std::endl;
        }
    }
}   

void HandlerCharacter::update(float dt, InputBufferer* input) {
    Unit::Move registeredMove = Unit::Move::MoveCount;

    for (Unit::Move move : order) {
        if (moveHandlers[static_cast<int>(move)] && moveHandlers[static_cast<int>(move)]->tryRegister(input)) {
            registeredMove = move;
            break;
        }
    }

    for (auto& handler : moveHandlers) {
        if (handler) {
            if (registeredMove != Unit::Move::MoveCount) {
                handler->listen(registeredMove);
            }
            handler->update(dt, input);
        }
    }
}

void HandlerCharacter::setOrder(std::vector<Unit::Move> newOrder) {
    order = std::move(newOrder);
}

void HandlerCharacter::setHandler(Unit::Move move, std::unique_ptr<MoveHandler> handler) {
    if (static_cast<int>(move) < 0 || static_cast<int>(move) >= Unit::NUM_MOVES) {
        std::cerr << "Warning: HandlerCharacter::setHandler - Invalid move type" << std::endl;
        return;
    }
    handler->registerCharacter(this);
    handler->registerPlayer(player);
    moveHandlers[static_cast<int>(move)] = std::move(handler);
}