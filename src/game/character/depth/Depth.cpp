#include "Depth.hpp"

#include "DepthGraphicsComponent.hpp"
#include "handler/DepthWideHandler.hpp"
#include "handler/DepthOffensiveHandler.hpp"

Depth::Depth() : HandlerCharacter("Depth", 570.0f, 330.0f, std::make_unique<DepthGraphicsComponent>()) {
    auto heroGfx = dynamic_cast<DepthGraphicsComponent*>(graphics.get());
    moveHandlers[static_cast<int>(Unit::Move::Wide)] = std::make_unique<DepthWideHandler>(heroGfx);
    moveHandlers[static_cast<int>(Unit::Move::Offensive)] = std::make_unique<DepthOffensiveHandler>(heroGfx);
    neutralize();
}

void Depth::neutralize() {
    order = { Unit::Move::Defensive, Unit::Move::Basic, Unit::Move::Wide, Unit::Move::Offensive };
}
