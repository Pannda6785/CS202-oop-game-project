#ifndef WORLD_H
#define WORLD_H

#include "IWorldView.h"
#include "Player.h"

class World : public IWorldView {
public:

    void update(float dt);
    
    std::vector<const Player*> getPlayers() const override;
    const Player* getPlayer(int playerId) const override;
    // std::vector<const Bullet*> getBullets() const override;

    void addPlayer(Player player);

private:
    std::vector<Player> players;

};

#endif // WORLD_H