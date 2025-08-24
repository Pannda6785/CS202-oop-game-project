#ifndef WORLD_BUILDER_HPP
#define WORLD_BUILDER_HPP

#include "../input/InputInterpreter.hpp"
#include "character/Character.hpp"
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
    std::vector<std::shared_ptr<InputInterpreter>> getInterpreters() const;

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

};

#endif // WORLD_BUILDER_HPP