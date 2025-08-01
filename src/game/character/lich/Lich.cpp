#include "Lich.hpp"

#include "LichGraphicsComponent.hpp"
#include "handler/LichBasicHandler.hpp"
#include "handler/LichWideHandler.hpp"
#include "handler/LichOffensiveHandler.hpp"

Lich::Lich() : HandlerCharacter("Lich", 525.0f, 300.0f, std::make_unique<LichGraphicsComponent>()) {
    auto lichGfx = dynamic_cast<LichGraphicsComponent*>(graphics.get());
    moveHandlers[static_cast<int>(Unit::Move::Basic)] = std::make_unique<LichBasicHandler>(lichGfx);
    moveHandlers[static_cast<int>(Unit::Move::Wide)] = std::make_unique<LichWideHandler>(lichGfx);
    moveHandlers[static_cast<int>(Unit::Move::Offensive)] = std::make_unique<LichOffensiveHandler>(lichGfx);
    neutralize();
}

void Lich::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Offensive, Unit::Move::Wide, Unit::Move::Basic };
}
