#ifndef HERO_BASIC_HANDLER_HPP
#define HERO_BASIC_HANDLER_HPP

#include "../../handlerCharacter/HoldHandler.hpp"

class HeroGraphicsComponent;

class HeroBasicHandler : public HoldHandler {
public:
    HeroBasicHandler(HeroGraphicsComponent* graphics);

    void update(float dt, const InputBufferer* input) override;
    void listen(Unit::Move move) override;

protected:
    void onHoldStart() override;
    void onHoldRelease(bool isInterupted = false) override;

private:
    HeroGraphicsComponent* graphics;
    void spawnBullet();
};

#endif // HERO_BASIC_HANDLER_HPP