#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

class IBulletSpawner;
class IPlayerControl;
class InputBufferer;

class Character {
public:
    Character(IBulletSpawner* bulletSpawnerRef);
    virtual ~Character() = default;

    virtual void init() = 0;
    virtual void update(float dt) = 0;

    std::string getName();
    float getMoveSpeed();
    float getFocusedSpeed();

    void registerPlayer(IPlayerControl* playerRef);
    void registerInputBufferer(InputBufferer* inputRef);

protected:
    IBulletSpawner* bulletSpawner;
    IPlayerControl* player = nullptr;
    InputBufferer* input = nullptr;

    std::string name;
    float moveSpeed;
    float focusedSpeed;
};

#endif // CHARACTER_HPP
