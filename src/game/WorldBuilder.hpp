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
    WorldBuilder();
    ~WorldBuilder() = default;

    void setPlayer(int id, const std::string& characterName, const InputInterpreter* interpreter);
    
    std::unique_ptr<World> getWorld();

private:
    struct PlayerConfig {
        std::string name;
        const InputInterpreter* interpreter;
        
        PlayerConfig() : name(""), interpreter(nullptr) {}
    };

    std::vector<PlayerConfig> playerConfigs;
    std::unique_ptr<Character> createCharacter(const std::string& characterName);    

};

#endif // WORLD_BUILDER_HPP