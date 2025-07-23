#include "Redhood.hpp"

#include "RedhoodGraphicsComponent.hpp"

Redhood::Redhood() : HandlerCharacter("Redhood", 750.0f, 390.0f, std::make_unique<RedhoodGraphicsComponent>()) {
    neutralize();
}

void Redhood::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Offensive, Unit::Move::Wide, Unit::Move::Basic };
}
