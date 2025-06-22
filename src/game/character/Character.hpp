#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "CharacterGraphicsComponent.hpp"

#include <memory>
#include <string>

class IPlayerControl;
class InputBufferer;

class Character {
public:
    virtual ~Character() = default;

    void registerPlayer(IPlayerControl* playerRef);
    
    virtual void init() = 0;
    virtual void update(float dt, InputBufferer* input) = 0;

    std::string getName();
    float getMoveSpeed();
    float getFocusedSpeed();

    CharacterGraphicsComponent* getGraphics();

protected:
    IPlayerControl* player;
    std::unique_ptr<CharacterGraphicsComponent> graphics;

    std::string name;
    float moveSpeed;
    float focusedSpeed;
};

#endif // CHARACTER_HPP
