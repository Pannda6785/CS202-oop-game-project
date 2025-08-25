#ifndef WORLD_BUILDER_HPP
#define WORLD_BUILDER_HPP

#include "../input/InputInterpreter.hpp"
#include "character/Character.hpp"
#include "challenge/Challenge.hpp"
#include "World.hpp"
#include <string>
#include <vector>
#include <memory>

class WorldBuilder {
public:
    WorldBuilder(bool isVsPlayer = true);
    ~WorldBuilder() = default;

    void setPlayer(int id, const std::string& characterName, std::shared_ptr<InputInterpreter> interpreter);
    void setAI(int id, const std::string& characterName);
    void setChallenge(const std::string& challengeName);
    std::vector<std::shared_ptr<InputInterpreter>> getInterpreters() const;
    std::vector<std::string> getAvailableChallenges() const;
    std::array<bool, 6> getChallengeFlags() const;

    std::unique_ptr<World> getWorld();

private:
    struct PlayerConfig {
        std::string name;
        std::shared_ptr<InputInterpreter> interpreter;
        
        PlayerConfig() : name(""), interpreter(nullptr) {}
    };

    std::unique_ptr<World> world;
    std::vector<PlayerConfig> playerConfigs;
    bool isVsPlayer = true;
    std::unique_ptr<Character> createCharacter(const std::string& characterName);
    std::unique_ptr<Challenge> createChallenge(const std::string& challengeName);
    std::array<bool, 6> challengeFlags = {false, false, false, false, false, false};
};

#endif // WORLD_BUILDER_HPP