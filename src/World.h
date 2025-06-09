#ifndef WORLD_H
#define WORLD_H

#include "IWorldView.h"
#include "IBulletSpawner.h"
#include "Player.h"
#include "Bullet.h"

#include <memory>

class World : public IWorldView, public IBulletSpawner {
public:
    void update(float dt);
    
    const Player* getPlayer(int playerId) const override;
    std::vector<const Player*> getPlayers() const override;
    std::vector<const Bullet*> getBullets() const override;

    void addPlayer(std::unique_ptr<Player> player);
    void spawnBullet(std::unique_ptr<Bullet> bullet);

private:
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<Bullet>> bullets;
};

#endif // WORLD_H
