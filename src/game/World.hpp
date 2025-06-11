#ifndef WORLD_HPP
#define WORLD_HPP

#include "IWorldView.hpp"
#include "IBulletSpawner.hpp"
#include "player/Player.hpp"
#include "bullet/Bullet.hpp"

#include <memory>

class World : public IWorldView, public IBulletSpawner {
public:
    void update(float dt);
    void init();
    
    const Player* getPlayer(int playerId) const override;
    std::vector<const Player*> getPlayers() const override;
    std::vector<const Bullet*> getBullets() const override;

    void addPlayer(std::unique_ptr<Player> player);
    void spawnBullet(std::unique_ptr<Bullet> bullet);

private:
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<Bullet>> bullets;

    void handleCollisions();
};

#endif // WORLD_HPP
