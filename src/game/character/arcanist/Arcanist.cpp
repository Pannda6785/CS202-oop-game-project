#include "Arcanist.hpp"

#include "ArcanistGraphicsComponent.hpp"

#include "handler/ArcanistBasicHandler.hpp"
#include "handler/ArcanistWideHandler.hpp"
#include "handler/ArcanistOffensiveHandler.hpp"
#include "handler/ArcanistDefensiveHandler.hpp"

Arcanist::Arcanist() : HandlerCharacter("Arcanist", 600.0f, 360.0f, std::make_unique<ArcanistGraphicsComponent>()) {
    auto arcanistGfx = dynamic_cast<ArcanistGraphicsComponent*>(graphics.get());
    moveHandlers[static_cast<int>(Unit::Move::Basic)] = std::make_unique<ArcanistBasicHandler>(arcanistGfx);
    moveHandlers[static_cast<int>(Unit::Move::Wide)] = std::make_unique<ArcanistWideHandler>(arcanistGfx);
    moveHandlers[static_cast<int>(Unit::Move::Offensive)] = std::make_unique<ArcanistOffensiveHandler>(arcanistGfx);
    moveHandlers[static_cast<int>(Unit::Move::Defensive)] = std::make_unique<ArcanistDefensiveHandler>(arcanistGfx);
    neutralize();
}

void Arcanist::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Offensive, Unit::Move::Basic, Unit::Move::Wide };
}
