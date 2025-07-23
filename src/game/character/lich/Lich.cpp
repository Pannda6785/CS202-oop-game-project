#include "Lich.hpp"

#include "LichGraphicsComponent.hpp"

Lich::Lich() : HandlerCharacter("Lich", 525.0f, 300.0f, std::make_unique<LichGraphicsComponent>()) {
    neutralize();
}

void Lich::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Offensive, Unit::Move::Wide, Unit::Move::Basic };
}
