#include "Hero.hpp"

#include "HeroGraphicsComponent.hpp"

#include "handler/HeroBasicHandler.hpp"
#include "handler/HeroWideHandler.hpp"
#include "handler/HeroOffensiveHandler.hpp"
#include "handler/HeroDefensiveHandler.hpp"

Hero::Hero() : HandlerCharacter("Hero", 690.0f, 120.0f, std::make_unique<HeroGraphicsComponent>()) {
    auto heroGfx = dynamic_cast<HeroGraphicsComponent*>(graphics.get());
    moveHandlers[static_cast<int>(Unit::Move::Basic)] = std::make_unique<HeroBasicHandler>(heroGfx);
    moveHandlers[static_cast<int>(Unit::Move::Wide)] = std::make_unique<HeroWideHandler>(heroGfx);
    moveHandlers[static_cast<int>(Unit::Move::Offensive)] = std::make_unique<HeroOffensiveHandler>(heroGfx);
    moveHandlers[static_cast<int>(Unit::Move::Defensive)] = std::make_unique<HeroDefensiveHandler>(heroGfx);
    neutralize();
}

void Hero::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Offensive, Unit::Move::Wide, Unit::Move::Basic };
}
