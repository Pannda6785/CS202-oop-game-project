#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <memory>
#include <string>

#include "IWorldView.h"
#include "InputHandler.h"
// #include "Character.h"
// #include "HitBox.h"
#include "Renderer.h"

class Player {
public:
    // Player(int playerId, std::shared_ptr<InputInterpreter> inputInterpreter, std::weak_ptr<IWorldView> worldView, std::weak_ptr<IBulletSpawner> bulletSpawner);
    Player(int playerId, std::shared_ptr<InputInterpreter> inputInterpreter, IWorldView* worldView);

    void update(float dt);
    void render(Renderer& renderer) const;

    int getId() const { return playerId; }
    std::string getCharacterName() const { return playerId == 0 ? "Blue Maiden" : "Red Maiden"; } // TO DO: Replace with character->getName() when Character is used
    int getHealth() const { return health; }
    int getStock() const { return stock; }
    // const HitBox& getHitBox() const { return hitbox; }
    const Unit::Vec2D& getPos() const { return pos; }
    const Unit::Vec2D& getArrow() const { return arrow; }
    const std::array<float, 4>& getCooldown() const { return cooldown; }
    // const std::unordered_map<Unit::Modifier, float>& getModifiers() const { return modifiers; }
    // const std::unordered_map<Unit::StatusEffect, float>& getStatusEffects() const { return statusEffect; }
    
    void setHealth(int h);
    void setStock(int s);
    void setPos(const Unit::Vec2D& position);

    void registerHit();
    void applyCooldown(Unit::Move, float cd);
    void applyStatusEffect();
    void applyModifier();

    void roundReset();
    
private:
    IWorldView* world;
    // std::IBulletSpawner* bulletSpawner;

    InputHandler input;
    // Character character;

    int playerId;
    int health;
    int stock;

    // HitBox hitbox;

    Unit::Vec2D pos;
    Unit::Vec2D arrow;

    std::array<float, Unit::NUM_MOVES> cooldown;
    // std::unordered_map<Unit::Modifier, float> modifiers;
    // std::unordered_map<Unit::StatusEffect, float> statusEffect;

    // Helper function (optional)
    void updateArrow(float dt);
    void updateCooldowns(float dt);
    void updateModifiers(float dt);
    void updateStatusEffects(float dt);
};


#endif // PLAYER_H
