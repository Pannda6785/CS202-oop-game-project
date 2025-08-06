#include "Stormbeast.hpp"

#include "StormbeastGraphicsComponent.hpp"

Stormbeast::Stormbeast() : HandlerCharacter("Stormbeast", 960.0f, 270.0f, std::make_unique<StormbeastGraphicsComponent>()) {
    neutralize();
}

void Stormbeast::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Offensive, Unit::Move::Wide, Unit::Move::Basic };
}
