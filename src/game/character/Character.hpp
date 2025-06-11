#ifndef CHARACTER_HPP
#define CHARACTER_HPP

class Character {
public:
    virtual ~Character() = default;
    
    virtual void update(float dt) = 0;

    // Accessors
    virtual std::string getName() const = 0;
    virtual float getMoveSpeed() const = 0;
    virtual float getFocusedSpeed() const = 0;

    // void registerPlayer(Player* playerRef);
    // void registerPlayer(Player* playerRef);

// protected:
//     IPlayerForCharacter* player;
//     std::string name;
//     float moveSpeed;
//     float focusedSpeed; 
};

#endif // CHARACTER_HPP
