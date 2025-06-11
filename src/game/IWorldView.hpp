#ifndef I_WORLD_VIEW_HPP
#define I_WORLD_VIEW_HPP

#include <vector>

class Player;
class Bullet;

class IWorldView {
public:
    virtual ~IWorldView() = default;

    virtual const Player* getPlayer(int playerId) const = 0;
    virtual std::vector<const Player*> getPlayers() const = 0;
    virtual std::vector<const Bullet*> getBullets() const = 0;
};

#endif // I_WORLD_VIEW_HPP