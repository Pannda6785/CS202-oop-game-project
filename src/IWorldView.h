#ifndef I_WORLD_VIEW_H
#define I_WORLD_VIEW_H

#include <vector>

class Player;

class IWorldView {
public:
    virtual ~IWorldView() = default;

    virtual std::vector<const Player*> getPlayers() const = 0;
    virtual const Player* getPlayer(int playerId) const = 0;
    // virtual std::vector<const Bullet*> getBullets() const = 0;
};

#endif // I_WORLD_VIEW_H