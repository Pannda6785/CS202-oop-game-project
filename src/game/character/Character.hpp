#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "CharacterGraphicsComponent.hpp"

#include <memory>
#include <string>

class Player;
class InputBufferer;

class Character {
public:
    Character(std::string name, float moveSpeed, float focusedSpeed, std::unique_ptr<CharacterGraphicsComponent> graphics);
    virtual ~Character() = default;

    virtual void registerPlayer(Player* playerRef);
    
    virtual void init();
    virtual void update(float dt, InputBufferer* input) = 0;

    std::string getName() const;
    float getMoveSpeed() const;
    float getFocusedSpeed() const;

    CharacterGraphicsComponent* getGraphics();

protected:
    Player* player;
    
    std::unique_ptr<CharacterGraphicsComponent> graphics;
    std::string name;
    float moveSpeed;
    float focusedSpeed;
};

#endif // CHARACTER_HPP
