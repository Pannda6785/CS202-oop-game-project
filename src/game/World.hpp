#ifndef WORLD_HPP
#define WORLD_HPP

#include "IWorldView.hpp"
#include "IBulletSpawner.hpp"
#include "player/Player.hpp"
#include "bullet/Bullet.hpp"
#include "pattern/Pattern.hpp"
#include "devtool/DevTool.hpp"

#include <memory>

class World : public IWorldView, public IBulletSpawner {
    friend class DevTool;
public:
    void update(float dt);
    void init();
    
    const Player* getPlayer(int playerId) const override;
    std::vector<const Player*> getPlayers() const override;
    std::vector<const Bullet*> getBullets() const override;

    void addPlayer(std::unique_ptr<Player> player);
    void addPattern(std::unique_ptr<Pattern> pattern);
    void spawnBullet(std::shared_ptr<Bullet> bullet);

private:
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::shared_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Pattern>> patterns;
    std::unique_ptr<DevTool> devTool;

    std::vector<std::shared_ptr<Bullet>> pendingBullets;

    void handleCollisions();
};

#endif // WORLD_HPP
