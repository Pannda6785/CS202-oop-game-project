#include "Priestess.hpp"

#include "PriestessGraphicsComponent.hpp"

#include "PriestessBasicHandler.hpp"
#include "PriestessWideHandler.hpp"
#include "PriestessOffensiveHandler.hpp"
#include "PriestessDefensiveHandler.hpp"

Priestess::Priestess() : HandlerCharacter("Priestess", 630.0f, 240.0f, std::make_unique<PriestessGraphicsComponent>()) {
    auto priestessGfx = dynamic_cast<PriestessGraphicsComponent*>(graphics.get());
    moveHandlers[static_cast<int>(Unit::Move::Basic)] = std::make_unique<PriestessBasicHandler>(priestessGfx);
    moveHandlers[static_cast<int>(Unit::Move::Wide)] = std::make_unique<PriestessWideHandler>(priestessGfx);
    moveHandlers[static_cast<int>(Unit::Move::Offensive)] = std::make_unique<PriestessOffensiveHandler>(priestessGfx);
    moveHandlers[static_cast<int>(Unit::Move::Defensive)] = std::make_unique<PriestessDefensiveHandler>(priestessGfx);
    neutralize();
}

void Priestess::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Offensive, Unit::Move::Wide, Unit::Move::Basic };
}