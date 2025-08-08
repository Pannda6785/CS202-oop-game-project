#ifndef ARCANIST_OFFENSIVE_HANDLER_HPP
#define ARCANIST_OFFENSIVE_HANDLER_HPP

#include "../../handlerCharacter/TapHandler.hpp"

class ArcanistGraphicsComponent;
class DeathToll;

class ArcanistOffensiveHandler : public TapHandler {
    static constexpr float COOLDOWN = 9.0f;
    static constexpr float MOVEMENT_LOCK = 0.250f;
    static constexpr float ACTION_LOCK = 0.600f;

public:
    ArcanistOffensiveHandler(ArcanistGraphicsComponent* graphics);

protected:
    void tap(bool isFocusing) override;

private:
    ArcanistGraphicsComponent* graphics;
};

#endif // ARCANIST_OFFENSIVE_HANDLER_HPP