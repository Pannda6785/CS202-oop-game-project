#include "Priestess.hpp"

#include "PriestessGraphicsComponent.hpp"

#include "../../IBulletSpawner.hpp"
#include "../../player/IPlayerControl.hpp"
#include "../../player/InputBufferer.hpp"

#include <cmath>
#include <memory>

Priestess::Priestess() : Character("Priestess", 630.0f, 240.0f, std::make_unique<PriestessGraphicsComponent>()) {}

void Priestess::init() {

}

void Priestess::update(float dt, InputBufferer* input) {
    
    

}
