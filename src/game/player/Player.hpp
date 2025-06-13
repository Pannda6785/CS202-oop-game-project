#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "IPlayerControl.hpp"
#include "IPlayerView.hpp"

#include "InputBufferer.hpp"
#include "../character/Character.hpp"
#include "../character/CharacterGraphicsComponent.hpp"
#include "../hitbox/Hitbox.hpp"

#include <array>
#include <memory>
#include <string>

class IWorldView;

class Player : public IPlayerControl, public IPlayerView {
public:
    Player(int playerId, IWorldView* worldView);

    // Update methods
    void init();
    void update(float dt);
    void takeHit();
    void confirmHit();
    void roundReset();

    // Register components, these must be called before the game starts (init())
    void registerInputInterpreter(std::shared_ptr<InputInterpreter> inputInterpreter);
    void registerCharacter(std::unique_ptr<Character> character);
    void registerGraphicsComponent(std::unique_ptr<CharacterGraphicsComponent> graphicsComponent);

    // Life data
    int getPlayerId() const override;
    int getHealth() const override;
    int getStock() const override;
    void setHealth(int h);
    void setStock(int s);
    const Hitbox* getHitbox() const override;
    
    // Positional data
    Unit::Vec2D getPosition() const override;
    Unit::Vec2D getArrow() const override;
    Unit::Vec2D getMovement() const override;
    Unit::Vec2D getTargetPosition() const override;
    void setPosition(const Unit::Vec2D& pos) override;
    
    // Status data
    float getInvincibility() const override;
    const std::array<std::pair<float, float>, Unit::NUM_MODIFIERS>& getModifiers() const override;
    const std::array<float, Unit::NUM_LOCKS>& getLocks() const override;
    void applyInvincibility(float duration, bool force = false) override;
    void applyLock(Unit::Lock lock, float duration, bool force = false) override;
    void applyModifier(Unit::Modifier mod, float duration, float value, bool force = false) override;

    // Character data

private:
    IWorldView* world;

    // Behavioral components
    std::unique_ptr<InputBufferer> input;
    std::unique_ptr<Character> character;
    std::unique_ptr<CharacterGraphicsComponent> graphics;

    // Basic stats
    int playerId;
    int health;
    int stock;
    std::unique_ptr<Hitbox> hitbox;

    // Positional data
    Unit::Vec2D pos;
    Unit::Vec2D arrow;
    Unit::Vec2D movement;

    // State trackers
    float invincibility;
    std::array<float, Unit::NUM_LOCKS> locks{};
    std::array<std::pair<float, float>, Unit::NUM_MODIFIERS> modifiers{}; // duration and values

    // Helpers
    void updateMovement(float dt);
    void updateArrow(float dt);
    void updateLocks(float dt);
    void updateModifiers(float dt);
};

#endif // PLAYER_HPP
