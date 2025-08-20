#ifndef HERO_OF_FROST_HEALTH_BAR_HPP
#define HERO_OF_FROST_HEALTH_BAR_HPP

#include "../HealthBar.hpp"

class HeroOfFrostHealthBar : public HealthBar {
public:
    HeroOfFrostHealthBar(bool isLeftSide = true);
    ~HeroOfFrostHealthBar() override = default;
};

#endif // HERO_OF_FROST_HEALTH_BAR_HPP