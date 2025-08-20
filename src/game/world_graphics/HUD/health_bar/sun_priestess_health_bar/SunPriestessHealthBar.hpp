#ifndef SUN_PRIESTESS_HEALTH_BAR_HPP
#define SUN_PRIESTESS_HEALTH_BAR_HPP

#include "../HealthBar.hpp"

class SunPriestessHealthBar : public HealthBar {
public:
    SunPriestessHealthBar(bool isLeftSide = true);
    ~SunPriestessHealthBar() override = default;
};

#endif // SUN_PRIESTESS_HEALTH_BAR_HPP