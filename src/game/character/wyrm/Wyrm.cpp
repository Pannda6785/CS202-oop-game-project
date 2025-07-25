#include "Wyrm.hpp"

#include "WyrmGraphicsComponent.hpp"

#include "handler/WyrmBasicHandler.hpp"
#include "handler/WyrmWideHandler.hpp"
// #include "handler/WyrmOffensiveHandler.hpp"
#include "handler/WyrmDefensiveHandler.hpp"

Wyrm::Wyrm() : HandlerCharacter("Wyrm", 780.0f, 390.0f, std::make_unique<WyrmGraphicsComponent>()) {
    auto wyrmGfx = dynamic_cast<WyrmGraphicsComponent*>(graphics.get());
    moveHandlers[static_cast<int>(Unit::Move::Basic)] = std::make_unique<WyrmBasicHandler>(wyrmGfx);
    moveHandlers[static_cast<int>(Unit::Move::Wide)] = std::make_unique<WyrmWideHandler>(wyrmGfx);
    // moveHandlers[static_cast<int>(Unit::Move::Offensive)] = std::make_unique<WyrmOffensiveHandler>(wyrmGfx);
    moveHandlers[static_cast<int>(Unit::Move::Defensive)] = std::make_unique<WyrmDefensiveHandler>(wyrmGfx);
    neutralize();
}

void Wyrm::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Basic, Unit::Move::Wide };
    // order = { Unit::Move::Defensive, Unit::Move::Offensive, Unit::Move::Wide, Unit::Move::Basic };
}