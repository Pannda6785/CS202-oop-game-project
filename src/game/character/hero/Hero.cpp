#include "Hero.hpp"

#include "HeroGraphicsComponent.hpp"

Hero::Hero() : HandlerCharacter("Hero", 690.0f, 120.0f, std::make_unique<HeroGraphicsComponent>()) {
    neutralize();
}

void Hero::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Offensive, Unit::Move::Wide, Unit::Move::Basic };
}
