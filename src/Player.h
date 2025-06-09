#ifndef PLAYER_H
#define PLAYER_H

#include "IPlayerForCharacter.h"
#include "IWorldView.h"
#include "IBulletSpawner.h"

#include "InputHandler.h"
#include "Character.h"
#include "Renderer.h"

#include "Hitbox.h"
#include "CircleHitbox.h"

#include <array>
#include <memory>
#include <string>

class Player : public IPlayerForCharacter {
public:
    Player(int playerId,
           std::unique_ptr<Character> character,
           std::shared_ptr<InputInterpreter> inputInterpreter,
           IWorldView* worldView,
           IBulletSpawner* bulletSpawner);

    // Main loop
    void update(float dt);
    void render(Renderer& renderer) const;
    
    // Life related
    void setHealth(int h);
    void setStock(int s);
    int getHealth() const;
    int getStock() const;
    const Hitbox* getHitbox() const;
    std::string getCharacterName() const;

    void registerHit();
    void roundReset();

    // Exposed methods
    int getId() const override;
    Unit::Vec2D getPosition() const override;
    Unit::Vec2D getArrow() const override;
    const std::array<float, Unit::NUM_MOVES>& getCooldown() const override;
    const std::array<float, Unit::NUM_STATUS_EFFECTS>& getStatusEffects() const override;
    const std::array<float, Unit::NUM_LOCKS>& getLocks() const override;

    void spawnBullet(std::unique_ptr<Bullet> bullet) override;

    void setPosition(const Unit::Vec2D& pos) override;
    void applyCooldown(Unit::Move move, float duration) override;
    void applyStatusEffect(Unit::StatusEffect effect, float duration) override;
    void applyLock(Unit::Modifier mod, float duration) override;
    void applyModifier(Unit::Modifier mod, float duration, float value) override;

private:
    // World interaction interfaces
    IWorldView* world;
    IBulletSpawner* bulletSpawner;

    // Behavioral components
    std::unique_ptr<InputHandler> input;
    std::unique_ptr<Character> character;

    // Basic stats
    int playerId;
    int health;
    int stock;

    // Positional data
    Unit::Vec2D pos;
    Unit::Vec2D arrow;
    CircleHitbox hitbox;

    // State trackers
    std::array<float, Unit::NUM_MOVES> cooldown{};
    std::array<float, Unit::NUM_STATUS_EFFECTS> statusEffects{};
    std::array<float, Unit::NUM_LOCKS> locks{};
    std::array<std::pair<float, float>, Unit::NUM_MODIFIERS> modifierValues{};

    // Helpers
    void updateArrow(float dt);
    void updateCooldowns(float dt);
    void updateStatusEffects(float dt);
    void updateLocks(float dt);
    void updateModifiers(float dt);
    void _render(Renderer& renderer) const;
};

#endif // PLAYER_H
