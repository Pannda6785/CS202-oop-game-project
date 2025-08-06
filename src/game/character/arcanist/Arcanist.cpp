#include "Arcanist.hpp"

#include "ArcanistGraphicsComponent.hpp"

Arcanist::Arcanist() : HandlerCharacter("Arcanist", 600.0f, 360.0f, std::make_unique<ArcanistGraphicsComponent>()) {
    neutralize();
}

void Arcanist::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Offensive, Unit::Move::Wide, Unit::Move::Basic };
}
