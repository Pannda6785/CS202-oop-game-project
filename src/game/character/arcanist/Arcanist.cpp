#include "Arcanist.hpp"

#include "ArcanistGraphicsComponent.hpp"

#include "handler/ArcanistOffensiveHandler.hpp"

Arcanist::Arcanist() : HandlerCharacter("Arcanist", 600.0f, 360.0f, std::make_unique<ArcanistGraphicsComponent>()) {
    auto arcanistGfx = dynamic_cast<ArcanistGraphicsComponent*>(graphics.get());
    moveHandlers[static_cast<int>(Unit::Move::Offensive)] = std::make_unique<ArcanistOffensiveHandler>(arcanistGfx);
    neutralize();
}

void Arcanist::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Offensive, Unit::Move::Wide, Unit::Move::Basic };
}
