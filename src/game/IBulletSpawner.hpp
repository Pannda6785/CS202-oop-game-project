#ifndef I_BULLET_SPAWNER_HPP
#define I_BULLET_SPAWNER_HPP

#include <memory>

class Bullet;

class IBulletSpawner {
public:
    virtual ~IBulletSpawner() = default;

    virtual void spawnBullet(std::unique_ptr<Bullet> bullet) = 0;

};

#endif // I_BULLET_SPAWNER_HPP