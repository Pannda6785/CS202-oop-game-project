#ifndef HERO_GRAPHICS_COMPONENT_HPP
#define HERO_GRAPHICS_COMPONENT_HPP

#include "../CharacterGraphicsComponent.hpp"

#include <deque>
#include <string>

class HeroGraphicsComponent : public CharacterGraphicsComponent {
public:
    HeroGraphicsComponent();
    ~HeroGraphicsComponent() override;

    void useBasic(int step);
    void useWide();
    void roll();
    void stun();

protected:
    void loadTextures() override;
    void unloadTextures() override {};
    bool characterSpecificUpdate(float dt) override;

private:
    std::deque<std::string> slashBuffer;

};

#endif // HERO_GRAPHICS_COMPONENT_HPP
