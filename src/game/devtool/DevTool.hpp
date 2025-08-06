#ifndef DEV_TOOL_HPP
#define DEV_TOOL_HPP

class World;

class DevTool {
public:
    explicit DevTool(World* world);

    void update(float dt);
    float getTimeScale() const;
    static bool isHitboxEnabled();

private:
    World* world;
    float timeScale = 1.0f;
    static bool hitboxEnabled;

    void toggleHitbox();
    void resetCooldown();
    void toggleInvincibility();
    void timeDown();
    void timeUp();
    void clearBullets();
    void log();
};

#endif // DEV_TOOL_HPP