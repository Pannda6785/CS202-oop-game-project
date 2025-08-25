#ifndef WORLD_HPP
#define WORLD_HPP

#include "IWorldView.hpp"
#include "IBulletSpawner.hpp"
#include "player/Player.hpp"
#include "bullet/Bullet.hpp"
#include "pattern/Pattern.hpp"
#include "challenge/Challenge.hpp"
#include "devtool/DevTool.hpp"

#include "world_graphics/combat_feedback/CombatFeedbackManager.hpp"
#include "world_graphics/HUD/HUD.hpp"
#include "../UI/game_state/versus_mode_state/ribbon_effect/MovingTextTileManager.hpp"
#include "world_graphics/WorldCamera.hpp"
#include "world_graphics/WorldBackground.hpp"

#include <memory>

class World : public IWorldView, public IBulletSpawner {
    static constexpr float FREEZE_DURATION = 0.5f;
    static constexpr float RESET_ROUND_DELAY = 0.75f;
    static constexpr float END_GAME_DELAY = 1.1f;

    friend class DevTool;
    friend class Challenge;

public:
    World();

    void update(float dt);
    void init();
    bool isGameEnded() const;
    
    const Player* getPlayer(int playerId) const override;
    std::vector<const Player*> getPlayers() const override;
    std::vector<const Bullet*> getBullets() const override;

    void addPlayer(std::unique_ptr<Player> player);
    void spawnBullet(std::shared_ptr<Bullet> bullet);
    void addPattern(std::unique_ptr<Pattern> pattern, float time = 0.0f);
    void addChallenge(std::unique_ptr<Challenge> challenge, float time = 0.0f);

    std::string getFinalResults() const;

private:
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::shared_ptr<Bullet>> bullets;
    std::vector<std::unique_ptr<Pattern>> patterns;
    std::unique_ptr<DevTool> devTool;
    std::unique_ptr<WorldCamera> camera;

    std::vector<std::shared_ptr<Bullet>> pendingBullets;
    std::vector<std::pair<std::unique_ptr<Pattern>, float>> pendingPatterns;
    std::vector<std::pair<std::unique_ptr<Challenge>, float>> pendingChallenges;

    std::unique_ptr<WorldBackground> background;
    std::unique_ptr<HUD> hud;
    std::unique_ptr<CombatFeedbackManager> combatFeedbackManager;
    std::unique_ptr<MovingTextTileManager> ribbonManager;

    float freezeTimer = 0.0f;
    float resetRoundTimer = 1e9;
    float endGameTimer = 1e9;
    bool gameEnded = false;

    void handlePendings(float dt);
    void handleCollisions();
    void registerHit(const std::vector<int>& hitPlayers);
    void endGame();
    void resetRound();
};

#endif // WORLD_HPP
