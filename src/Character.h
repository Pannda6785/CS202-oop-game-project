#ifndef CHARACTER_H
#define CHARACTER_H

#include "IPlayerForCharacter.h"
#include "InputHandler.h"
#include "Bullet.h"
// #include "CharacterGraphicsComponent.h"

#include <string>

class Character {
public:
    virtual ~Character() = default;
    
    virtual void update(float dt, const InputHandler& input) = 0;

    // Accessors
    virtual std::string getName() const = 0;
    virtual float getMoveSpeed() const = 0;
    virtual float getFocusedSpeed() const = 0;
    // virtual const CharacterGraphicComponent& getGraphics() const = 0;

    void registerPlayer(IPlayerForCharacter* playerRef) { player = playerRef; }

protected:
    IPlayerForCharacter* player;
    std::string name;
    float moveSpeed;
    float focusedSpeed; 
};

#endif // CHARACTER_H
