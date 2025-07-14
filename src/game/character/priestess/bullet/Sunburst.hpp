#ifndef SUNBURST_HPP
#define SUNBURST_HPP

#include "../../../bullet/Bullet.hpp"
#include "SunburstGraphicsComponent.hpp"

#include <memory>

class Sunburst : public Bullet {
    static constexpr float BASE_RADIUS = 240.0f;   
    static constexpr float ACTIVE_TIME = 0.9f; // how long after start up that it linger in place
    static constexpr float BLOOM_TIME = 0.15f;
    static constexpr float BASE_STARTUP = 0.780f;
    static constexpr float FOCUS_STARTUP = 0.858f; // use this instead when focused
    static constexpr float DISTANCE_SCALAR = 0.55f; // per distance startup
    static constexpr float FOCUS_DISTANCE_SHORTENING = 200.0f; // 200px closer  
    static constexpr float SPEED = 1000.0f / DISTANCE_SCALAR; // 1818 units per second for 0.55

public:
    Sunburst(int id, Unit::Vec2D pos, Unit::Vec2D arrow, Unit::Vec2D target, bool focused);

    void update(float dt) override;
    bool isDone() const override;

    Unit::Vec2D getPosition() const;
    bool isStartingUp() const;
    bool isFocused() const;
    float getRadius() const;
    float getRingRadius() const;

private:
    std::unique_ptr<SunburstGraphicsComponent> graphics;

    Unit::Vec2D pos;
    Unit::Vec2D vel;
    bool focused;
    
    float toTravel;
    float startupTime;
    float activeTime;
    float bloomTime;
    bool startedup;
};

#endif // SUNBURST_HPP
