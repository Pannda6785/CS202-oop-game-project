#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "InputBufferer.hpp"
#include "../character/Character.hpp"
#include "../hitbox/CircleHitbox.hpp"

#include <array>
#include <memory>
#include <string>

class IWorldView;
class IBulletSpawner;
class Bullet;

class Player {
    static constexpr float HITBOX_RADIUS = 1.5f;
    static constexpr float STOCK = 2;
    static constexpr float HEALTH = 4;
    int init_health;

public:
    Player(int playerId, IWorldView* worldView, IBulletSpawner* bulletSpawner,
            std::unique_ptr<Character> character, std::shared_ptr<InputInterpreter> inputInterpreter, int init_stock = STOCK, int init_health = HEALTH);

    // Update methods
    void init();
    void update(float dt);
    void takeHit();
    void confirmHit();
    void resetRound();

    // World interaction
    const IWorldView* getWorld() const;
    IBulletSpawner* getBulletSpawner() const;
    void spawnBullet(std::shared_ptr<Bullet> bullet);

    // Life data
    int getPlayerId() const;
    int getHealth() const;
    int getStock() const;
    const CircleHitbox* getHitbox() const;
    
    // Positional data
    Unit::Vec2D getPosition() const;
    Unit::Vec2D getArrow() const;
    Unit::Vec2D getMovement() const;
    Unit::Vec2D getTargetPosition() const;
    void setPosition(const Unit::Vec2D& pos);
    
    // Status data
    float getInvincibility(bool major = false) const;
    std::pair<float, float> getModifier(Unit::Modifier mod) const;
    float getLock(Unit::Lock lock) const;
    float getCooldown(Unit::Move move) const;

    void applyInvincibility(float duration, bool major, bool force = false);
    void applyModifier(Unit::Modifier mod, float duration, float value, bool force = false);
    void applyLock(Unit::Lock lock, float duration, bool force = false);
    void applyCooldown(Unit::Move move, float duration, bool force = false);
    void applyImplicitMoveLock(bool force = false);

    // Export data
    std::string getName() const;
    std::array<int, 4> getSignatureColor() const;
    bool isFocused() const;

private:
    IWorldView* world;
    IBulletSpawner* bulletSpawner;

    // Behavioral components
    std::unique_ptr<InputBufferer> input;
    std::unique_ptr<Character> character;

    // Life data
    int playerId;
    int health;
    int stock;
    std::unique_ptr<CircleHitbox> hitbox;

    // Positional data
    Unit::Vec2D pos;
    Unit::Vec2D arrow;
    Unit::Vec2D movement;

    // Status data
    std::array<float, 2> invincibility;
    std::array<std::pair<float, float>, Unit::NUM_MODIFIERS> modifiers{}; // duration and values
    std::array<float, Unit::NUM_LOCKS> locks{};
    std::array<float, Unit::NUM_MOVES> cooldown{};

    // Helpers
    void updateMovement(float dt);
    void updateArrow(float dt);
    void updateStatus(float dt);
};

#endif // PLAYER_HPP
