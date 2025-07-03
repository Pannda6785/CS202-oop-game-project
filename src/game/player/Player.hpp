#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "IPlayerControl.hpp"
#include "IPlayerView.hpp"

#include "InputBufferer.hpp"
#include "../character/Character.hpp"
#include "../hitbox/Hitbox.hpp"

#include <array>
#include <memory>
#include <string>

class IWorldView;
class IBulletSpawner;

class Player : public IPlayerControl, public IPlayerView {
public:
    Player(int playerId, IWorldView* worldView, IBulletSpawner* bulletSpawner,
            std::unique_ptr<Character> character, std::shared_ptr<InputInterpreter> inputInterpreter);

    // Update methods
    void init();
    void update(float dt);
    void takeHit();
    void confirmHit();
    void roundReset();

    // World interaction
    void spawnBullet(std::unique_ptr<Bullet> bullet);

    // Life data
    int getPlayerId() const override;
    int getHealth() const override;
    int getStock() const override;
    const Hitbox* getHitbox() const override;
    void setHealth(int h);
    void setStock(int s);
    
    // Positional data
    Unit::Vec2D getPosition() const override;
    Unit::Vec2D getArrow() const override;
    Unit::Vec2D getMovement() const override;
    Unit::Vec2D getTargetPosition() const override;
    void setPosition(const Unit::Vec2D& pos) override;
    
    // Status data
    float getInvincibility() const override;
    std::pair<float, float> getModifier(Unit::Modifier mod) const override;
    float getLock(Unit::Lock lock) const override;
    float getCooldown(Unit::Move move) const override;

    void applyInvincibility(float duration, bool force = false) override;
    void applyModifier(Unit::Modifier mod, float duration, float value, bool force = false) override;
    void applyLock(Unit::Lock lock, float duration, bool force = false) override;
    void applyCooldown(Unit::Move move, float duration, bool force = false) override;
    void applyImplicitMoveLock() override;

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
    std::unique_ptr<Hitbox> hitbox;

    // Positional data
    Unit::Vec2D pos;
    Unit::Vec2D arrow;
    Unit::Vec2D movement;

    // Status data
    float invincibility;
    std::array<std::pair<float, float>, Unit::NUM_MODIFIERS> modifiers{}; // duration and values
    std::array<float, Unit::NUM_LOCKS> locks{};
    std::array<float, Unit::NUM_MOVES> cooldown{};

    // Helpers
    void updateMovement(float dt);
    void updateArrow(float dt);
    void updateStatus(float dt);
};

#endif // PLAYER_HPP
