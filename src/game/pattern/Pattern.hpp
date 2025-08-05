#ifndef PATTERN_HPP
#define PATTERN_HPP

class IBulletSpawner;

class Pattern {
public:
    explicit Pattern(IBulletSpawner* spawner) : spawner(spawner) {}
    virtual ~Pattern() = default;

    virtual void init() = 0;
    virtual void update(float dt) = 0;

protected:
    IBulletSpawner* spawner;

};

#endif // PATTERN_HPP