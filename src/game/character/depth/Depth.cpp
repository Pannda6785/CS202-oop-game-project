#include "Depth.hpp"

#include "DepthGraphicsComponent.hpp"

Depth::Depth() : HandlerCharacter("Depth", 570.0f, 330.0f, std::make_unique<DepthGraphicsComponent>()) {
    neutralize();
}

void Depth::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Offensive, Unit::Move::Wide, Unit::Move::Basic };
}
